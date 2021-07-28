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

    //set texture


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