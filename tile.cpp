#include "tile.h"

Tile::Tile()
{
    initTile(0, 0, 0);
};

Tile::Tile(int x, int y, int height)
{
    initTile(x, y, height);
    this->height = height;
    this->x = x;
    this->y = y;
    obstruct = false;
    checked = false;
};

void Tile::initTile(int x, int y, int height)
{


    //make grid tile
    diamond.setPointCount(4);
    diamond.setPoint(0, sf::Vector2f(x, y));
    diamond.setPoint(1, sf::Vector2f(x + (height / 2), y + (height/4)));
    diamond.setPoint(2, sf::Vector2f(x, y + height/2));
    diamond.setPoint(3, sf::Vector2f(x - (height / 2), y + (height/4)));

    this->height = height;
    this->x = x;
    this->y = y;

    obstruct = false;
    rocks = false;
    checked = false;

};

void Tile::editColor()
{
    diamond.setFillColor(sf::Color(200, 200, 0));
};

void Tile::resetColor()
{
    diamond.setFillColor(sf::Color(255, 255, 255));
};

void Tile::initTexture(sf::Texture &texture)
{
    diamond.setTexture(&texture);
};

void Tile::setRandom(sf::Texture &organic, sf::Texture &rockTexture)
{
    int random = rand() % 25 - 1;
    //one in every 10 blocks will have organic materials
    if(random == 2)
    {
        diamond.setTexture(&organic);
    }

    //one in every 5 will be rocks
    else if(random == 3 || random == 4)
    {
        rocks = true;
        obstruct = true;
        
        //initializes rocks on the middle of the tile
        int rockx = x - (50 / 2);
        int rocky = (y + (getHeight()/3)) - (50);

        rockShape.setSize(sf::Vector2f(50,50));
        rockShape.setPosition(rockx, rocky);
        rockShape.setTexture(&rockTexture);
    }

};