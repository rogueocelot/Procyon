#include "game.h"

//constructors
Game::Game()
{
    initVariables();
    initWindow();
    initGrid();
    initRover();
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
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::Escape)
                {
                    window->close();
                    break;
                }
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

};

void Game::renderGrid()
{
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            window->draw(grid[i].at(j).getGrid());
        }
    }


}

void Game::renderRover()
{
    window->draw(rover.getRect());
}

//private

void Game::initVariables()
{
    window = nullptr;

    //game variables
    mouseDelta = 0;
    zoom = 1.0;
    roverSize = 50;

    move = false;
    moveX = 0;
    moveY = 0;
    skip = false;

    int nextX = 0;
    int nextY = 0;

    tileTexture.loadFromFile("textures/marsTerrain2.png");
    

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

    for (int i = 0; i < 5; i++)
    {
        x = startx;
        y = starty;

        for (int j = 0; j < 5; j++)
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
        
        //next destination
        //moves in 1 tile increments
        if (moveX != roverGridx && skip == false)
        {
            if(moveX < roverGridx && !grid[roverGridx - 1][roverGridy].getObstruct())
            {
                nextX = grid[roverGridx - 1][roverGridy].getX() - (roverSize / 2);
                nextY = (grid[roverGridx - 1][roverGridy].getY() + (grid[roverGridx][roverGridy].getHeight()/3)) - (roverSize);
                nextGridx = roverGridx - 1;
            }

            else if(moveX > roverGridx && !grid[roverGridx + 1][roverGridy].getObstruct())
            {
                nextX = grid[roverGridx + 1][roverGridy].getX() - (roverSize / 2);
                nextY = (grid[roverGridx + 1][roverGridy].getY() + (grid[roverGridx][roverGridy].getHeight()/3)) - (roverSize);
                nextGridx = roverGridx + 1;
            }

            //force the rover to change y if x is blocked
            else{
                if(!grid[roverGridx][roverGridy - 1].getObstruct())
                {
                    nextX = grid[roverGridx][roverGridy - 1].getX() - (roverSize / 2);
                    nextY = (grid[roverGridx][roverGridy - 1].getY() + (grid[roverGridx][roverGridy].getHeight()/3)) - (roverSize);
                    nextGridy = roverGridy - 1;
                }
                else if(!grid[roverGridx][roverGridy + 1].getObstruct())
                {
                    nextX = grid[roverGridx][roverGridy + 1].getX() - (roverSize / 2);
                    nextY = (grid[roverGridx][roverGridy + 1].getY() + (grid[roverGridx][roverGridy].getHeight()/3)) - (roverSize);
                    nextGridy = roverGridy + 1;
                }
            }
        }

        else if (moveY != roverGridy)
        {
            if(moveY < roverGridy && !grid[roverGridx][roverGridy - 1].getObstruct())
            {
                nextX = grid[roverGridx][roverGridy - 1].getX() - (roverSize / 2);
                nextY = (grid[roverGridx][roverGridy - 1].getY() + (grid[roverGridx][roverGridy].getHeight()/3)) - (roverSize);
                nextGridy = roverGridy - 1;
            }
            else if(moveY > roverGridy && !grid[roverGridx][roverGridy + 1].getObstruct())
            {
                nextX = grid[roverGridx][roverGridy + 1].getX() - (roverSize / 2);
                nextY = (grid[roverGridx][roverGridy + 1].getY() + (grid[roverGridx][roverGridy].getHeight()/3)) - (roverSize);
                nextGridy = roverGridy + 1;
            }

            //force rover to change x if y is blocked
            //have to use skip to skip the x checking until correct y
            else{
                if(!grid[roverGridx - 1][roverGridy].getObstruct())
                {
                    nextX = grid[roverGridx - 1][roverGridy].getX() - (roverSize / 2);
                    nextY = (grid[roverGridx - 1][roverGridy].getY() + (grid[roverGridx][roverGridy].getHeight()/3)) - (roverSize);
                    nextGridx = roverGridx - 1;
                    skip = true;
                }
                else if(!grid[roverGridx + 1][roverGridy].getObstruct())
                {
                    nextX = grid[roverGridx + 1][roverGridy].getX() - (roverSize / 2);
                    nextY = (grid[roverGridx + 1][roverGridy].getY() + (grid[roverGridx][roverGridy].getHeight()/3)) - (roverSize);
                    nextGridx = roverGridx + 1;
                    skip = true;
                }
            }
        }

        //can check x again
        else if(moveY == roverGridy)
        {
            skip = false;
        }


        //movement
        if(nextX < currentX)
        {
            currentX -= 2;
            rover.rectPosition(currentX, currentY - 200);
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
        }

        //after it reaches destination
        if (currentX == roverX && currentY == roverY)
        {
            //stop moving
            move = false;
            //set what grid square its on
            rover.gridPosition(moveX, moveY);
            grid[moveX][moveY].resetColor();
            //centers the view on the rover
            //view.setCenter(sf::Vector2f(currentX, currentY));
        }

    }

};