#include "game.h"

//constructors
Game::Game()
{
    initVariables();
    initWindow();
    initGrid();
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

};


//game drawing
void Game::render()
{
    //r, g, b, alpha (transparency)
    //clears old frame
    window->clear(sf::Color(100, 75, 178, 255));

    //draw game here
    renderGrid();

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

//private

void Game::initVariables()
{
    window = nullptr;

    //game logic variables

};


void Game::initWindow()
{
    videoMode.height = 600;
    videoMode.width = 800;

    window = new sf::RenderWindow(videoMode, "Procyon", sf::Style::Titlebar| sf::Style::Close);

    window->setFramerateLimit(60);
};

void Game::initGrid()
{
    vector<Tile> tempVec;
    Tile tempTile;

    int startx = 405;
    int starty = 20;
    int height = 150;

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
        startx = startx + (height/2) + 2;
        starty = starty + (height/4) + 2;
    }

    //testTile.initTile(400, 555, 100);

};