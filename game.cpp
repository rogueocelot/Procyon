#include "game.h"

//constructors
Game::Game()
{
    initVariables();
    initWindow();
    initGrid();
    initRover();
    initText();
};

Game::~Game()
{
    delete window;
};


//call game function updates
void Game::update()
{
    pollEvents();

    updateMousePos();

    //status/movement of rover
    updateRover();
    moveRover();

    if(digging)
    {
        Dig();
        digging = false;
    }

};


//game drawing
void Game::render()
{
    //r, g, b, alpha (transparency)
    //clears old frame
    window->clear(sf::Color(16, 16, 16, 255));

    window->setView(view);

    //draw game here
    renderGrid();
    renderRover();
    renderDig();
    renderText();

    //display game
    window->display();
};


void Game::pollEvents()
{
    //event polling
    while(window->pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::GainedFocus:
                focus = true;
                break;
            case sf::Event::LostFocus:
                focus = false;
                break;

            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::Space)
                {
                    digging = true;
                    break;
                }
            /*
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::Escape)
                {
                    window->close();
                    break;
                }*/
            /*
            case sf::Event::MouseWheelMoved:
                mouseDelta = event.mouseWheel.delta;
                if(mouseDelta > 0)
                {
                    zoom += mouseDelta * 0.05;
                    if (zoom <= 1.f)
                    {
                        view.zoom(zoom);
                    }
                    else{
                        zoom = 1;
                    }
                }
                else if(mouseDelta < 0)
                {
                    zoom -= mouseDelta * 0.05;
                    if (zoom >= 0.f)
                    {
                        view.zoom(zoom);
                    }
                    else{
                        zoom = 0;
                    }
                }
                break;*/
        }
    }

};


void Game::updateMousePos()
{
    //updates the mouse position (relative to window)
    mouseWindow = sf::Mouse::getPosition(*window);
    //updates mouse relative to view (using relative to window)
    mousePosition = window->mapPixelToCoords(mouseWindow);

};

void Game::updateRover()
{

    //this is all a mess
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        int mouseX = mousePosition.x;
        int mouseY = mousePosition.y;

        if(focus)
        {

            //check to see if a grid square was clicked
            for (int i = 0; i < grid.size(); i++)
            {
                for (int j = 0; j < grid[i].size(); j++)
                {
                    int x = grid[i][j].getX();
                    int y = grid[i][j].getY();
                    int height = grid[i][j].getHeight();
                    if(mouseX > x - (height/4) && mouseX < x + (height/4) && mouseY > y + (height/8) && mouseY < y + ((height/4) + (height/8)))
                    {
                        //selected grid changes color
                        //saves selected tile
                        //saves coords
                        if(move == false) 
                        {
                            grid[i][j].editColor();
                            moveX = i;
                            moveY = j;
                            move = true;
                        }
                    }
                    else
                    {
                        //other squares change back
                        grid[i][j].resetColor();
                        //for testing
                        //grid[2][3].editColor();
                    }
                }
            }
        }
    }

};

void Game::renderGrid()
{
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            window->draw(grid[i].at(j).getGrid());
            //draw rocks
            if(grid[i][j].getRocks() == true)
            {
                window->draw(grid[i][j].getRockShape());
            }
        }
    }


}

void Game::renderRover()
{
    rover.setText(roverTexture, direction);
    window->draw(rover.getRect());
}

void Game::renderDig()
{
    if(displayDig)
    {
        digCounter++;
        displayDig = false;
    }
    if(digCounter > 0)
    {
        scienceRect.setPosition(rover.getCurrentX(), rover.getCurrentY() - digCounter);
        window->draw(scienceRect);
        digCounter++;

        if(digCounter > 25)
        {
            digCounter = 0;
        }
    }
};

void Game::renderText()
{
    dispScience = "Science: ";
    stringstream strs;
    strs << science;
    dispScience = dispScience + strs.str();
    text.setPosition(0.f, 0.f);

    window->setView(UI);

    text.setString(dispScience);
    window->draw(text);

    window->setView(view);
};

//private

void Game::initVariables()
{
    window = nullptr;

    //game variables
    mouseDelta = 0;
    zoom = 1.0;
    roverSize = 50;
    terrainSize = 50;
    tileNum = 50;
    ordering = true;
    searching = true;


    digging = false;
    displayDig = false;
    digSize.x = 20;
    digSize.y = 20;
    science = 0;
    digCounter = 0;

    move = false;
    moveX = 0;
    moveY = 0;
    direction = 'n';

    int nextX = 0;
    int nextY = 0;

    tileTexture.loadFromFile("textures/marsTerrain2.png");
    roverTexture.loadFromFile("textures/rover.png");
    organicTexture.loadFromFile("textures/organic.png");
    rockTexture.loadFromFile("textures/marsRocks2.png");
    researchTexture.loadFromFile("textures/research.png");

    font.loadFromFile("assets/plex.ttf");

};


void Game::initWindow()
{
    videoMode.height = 600;
    videoMode.width = 800;

    window = new sf::RenderWindow(videoMode, "Procyon", sf::Style::Titlebar| sf::Style::Close);

    //defines view
    view.setCenter(sf::Vector2f(videoMode.width /2, videoMode.height/2));
    view.setSize(sf::Vector2f(videoMode.width, videoMode.height));

    //sets window view to view
    window->setView(view);

    window->setFramerateLimit(60);

    UI.setCenter(sf::Vector2f(videoMode.width / 2, videoMode.height/2));
    UI.setSize(sf::Vector2f(videoMode.width, videoMode.height));
    
};

void Game::initGrid()
{
    vector<Tile> tempVec;
    Tile tempTile;

    int startx = 405;
    int starty = 100;
    int height = 100;

    int x;
    int y;

    for (int i = 0; i < tileNum; i++)
    {
        x = startx;
        y = starty;

        for (int j = 0; j < tileNum; j++)
        {
            tempTile.initTile(x, y, height);
            tempVec.push_back(tempTile);
            x = x - (height/2) - 2;
            y = y + (height/4) + 2;

        }
        grid.push_back(tempVec);
        tempVec.clear();
        startx = startx + (height/2) + 2;
        starty = starty + (height/4) + 2;
    }


    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            grid[i][j].initTexture(tileTexture);
            //randomly places rocks and organic material, but not on starting square
            if(i != 2 && j != 2 && i != 0 && j != 0)
            {
                grid[i][j].setRandom(organicTexture, rockTexture);
            }
        }
    }

    //test stuff
    //grid[2][3].setObstruct(true);
    //grid[2][3].editColor();
};


void Game::initRover()
{
    //initializes rover on middle tile
    int roverx = grid[2].at(2).getX() - (roverSize / 2);
    int rovery = (grid[2].at(2).getY() + (grid[2].at(2).getHeight()/3)) - (roverSize);

    rover.initRect(roverx, rovery, roverSize);
    rover.setText(roverTexture, direction);
};

void Game::initText()
{
    text.setFont(font);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::White);
    text.setPosition(0.f, 0.f);

    dispScience = "Science: ";
};

void Game::moveRover()
{

    if(move)
    {   
        //current coords
        int currentX = rover.getCurrentX();
        int currentY = rover.getCurrentY();

        //current tile
        int roverGridx = rover.getGridX();
        int roverGridy = rover.getGridY();

        //next grid tile to move to
        int nextGridx = roverGridx;
        int nextGridy = roverGridy;

        //end destination
        int roverX = grid[moveX].at(moveY).getX() - (roverSize / 2);
        int roverY = (grid[moveX].at(moveY).getY() + (grid[moveX].at(moveY).getHeight()/3)) - (roverSize);

        //containers for pathfinding

        tempMove.x = roverGridx;
        tempMove.y = roverGridy;
        tempMove.prev = 777000;

        checking.push(tempMove);

        while(searching)
        {
            if(moveX == checking.front().x && moveY == checking.front().y)
            {
                searching = false;
            }
            if(checking.front().x - 1 >= 0 && !grid[checking.front().x - 1][checking.front().y].getObstruct() && !grid[checking.front().x - 1][checking.front().y].getChecked())
            {
                tempMove.x = checking.front().x - 1;
                tempMove.y = checking.front().y;
                tempMove.prev = checked.size();
                checking.push(tempMove);
            }
            if(checking.front().x + 1 < tileNum && !grid[checking.front().x + 1][checking.front().y].getObstruct() && !grid[checking.front().x + 1][checking.front().y].getChecked())
            {
                tempMove.x = checking.front().x + 1;
                tempMove.y = checking.front().y;
                tempMove.prev = checked.size();
                checking.push(tempMove);
            }
            if(checking.front().y - 1 >= 0 && !grid[checking.front().x][checking.front().y - 1].getObstruct() && !grid[checking.front().x][checking.front().y - 1].getChecked())
            {
                tempMove.x = checking.front().x;
                tempMove.y = checking.front().y - 1;
                tempMove.prev = checked.size();
                checking.push(tempMove);
            }
            if(checking.front().y + 1 < tileNum && !grid[checking.front().x][checking.front().y + 1].getObstruct() && !grid[checking.front().x][checking.front().y + 1].getChecked())
            {
                tempMove.x = checking.front().x;
                tempMove.y = checking.front().y + 1;
                tempMove.prev = checked.size();
                checking.push(tempMove);
            }
            checked.push_back(checking.front());
            //for testing
            //grid[checking.front().x][checking.front().y].editColor();
            grid[checking.front().x][checking.front().y].setChecked(true);
            checking.pop();
        }

        if (ordering)
        {
            path.push_back(checked.back());
        }

        while(ordering)
        {
            tempMove = path.front();
            path.push_front(checked.at(tempMove.prev));
            if(path.front().prev == 777000)
            {
                ordering = false;
            }
            //cout << tempMove.x << " " << tempMove.y << " " << tempMove.prev << endl;
        }

        nextX = grid[path.front().x][path.front().y].getX() - (roverSize / 2);
        nextY = (grid[path.front().x][path.front().y].getY() + (grid[path.front().x][path.front().y].getHeight()/3)) - (roverSize);
        nextGridx = path.front().x;
        nextGridy = path.front().y;
        //grid[nextGridx][nextGridy].editColor();

        //set rover sprite direction
        if(nextX < currentX && nextY < currentY){direction = 'w';}
        else if(nextX < currentX && nextY > currentY){direction = 's';}
        else if(nextX > currentX && nextY < currentY){direction = 'n';}
        else if(nextX > currentX && nextY > currentY){direction = 'e';}

        //movement
        if(nextX < currentX)
        {
            currentX -= 2;
            rover.rectPosition(currentX, currentY/* - 200*/);
        }

        if(nextY < currentY)
        {
            currentY -= 1;
            rover.rectPosition(currentX, currentY);
        }

        if(nextX > currentX)
        {
            currentX += 2;
            rover.rectPosition(currentX, currentY);
        }

        if(nextY > currentY)
        {
            currentY += 1;
            rover.rectPosition(currentX, currentY);
        }

        //after it moves one tile
        if (currentX == nextX && currentY == nextY)
        {
            //set what grid square its on
            rover.gridPosition(nextGridx, nextGridy);
            path.pop_front();

        }

        //after it reaches destination
        if (currentX == roverX && currentY == roverY)
        {
            //stop moving
            move = false;
            ordering = true;
            searching = true;
            //set what grid square its on
            rover.gridPosition(moveX, moveY);
            grid[moveX][moveY].resetColor();
            //centers the view on the rover
            view.setCenter(sf::Vector2f(currentX ,currentY + 100));

            //clear containers
            list<Move>().swap(path);
            //path.clear();
            vector<Move>().swap(checked);
            queue<Move>().swap(checking);
            //checked.clear();
            /*while(!checking.empty())
            {
                checking.pop();
            }*/
            for (int idx = 0; idx < grid.size(); idx++)
            {
                for (int jdx = 0; jdx < grid[idx].size(); jdx++)
                {
                    grid[idx][jdx].setChecked(false);
                }
            }

        }

    }

};

void Game::Dig()
{
    if(grid[rover.getGridX()][rover.getGridY()].getDiggable())
    {
        scienceRect.setPosition(rover.getCurrentX(), rover.getCurrentY());
        scienceRect.setSize(digSize);
        scienceRect.setFillColor(sf::Color(100, 75, 178));
        scienceRect.setTexture(&researchTexture);

        displayDig = true;
        science++;
        grid[rover.getGridX()][rover.getGridY()].setDiggable(false);
        grid[rover.getGridX()][rover.getGridY()].initTexture(tileTexture);
    }
};