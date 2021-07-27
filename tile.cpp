#include "tile.h"

Tile::Tile()
{
    initTile(0, 0, 0);
};

Tile::Tile(int x, int y, int height)
{
    initTile(x, y, height);
};

void Tile::initTile(int x, int y, int height)
{
    diamond.setPointCount(4);
    diamond.setPoint(0, sf::Vector2f(x, y));
    diamond.setPoint(1, sf::Vector2f(x + (height / 2), y + (height/4)));
    diamond.setPoint(2, sf::Vector2f(x, y + height/2));
    diamond.setPoint(3, sf::Vector2f(x - (height / 2), y + (height/4)));

    /*
    diamond.setPointCount(4);
    diamond.setPoint(0, sf::Vector2f(500, 500));
    diamond.setPoint(1, sf::Vector2f(550 , 550));
    diamond.setPoint(2, sf::Vector2f(500 , 600));
    diamond.setPoint(3, sf::Vector2f(450 , 550));
    */
}