#include "rover.h"

Rover::Rover()
{

};

Rover::Rover(int height, int width)
{
    this->height = height;
    this->width = width;
};

void Rover::initRect(int x, int y, int size)
{
    //load texture
    


    //create rover rect
    rectSize.x = size;
    rectSize.y = size;
    rect.setPosition(x, y);
    rect.setSize(rectSize);
    rect.setFillColor(sf::Color(100, 75, 178));
    gridX = 2;
    gridY = 2;

    currentX = x;
    currentY = y;


    //set texture


};

void Rover::rectPosition(int x, int y)
{
    rect.setPosition(x, y);

    currentX = x;
    currentY = y;
};

void Rover::gridPosition(int x, int y)
{
    gridX = x;
    gridY = y;
};

void Rover::setTexture(sf::Texture &texture, char direction)
{
    rect.setTexture(&texture);

    if (direction == 'n')
    {
        rect.setTextureRect(sf::IntRect(0, 0, 50, 50));
    }
    else if (direction == 'e')
    {
        rect.setTextureRect(sf::IntRect(102, 0, 50, 50));
    }
    else if (direction == 's')
    {
        rect.setTextureRect(sf::IntRect(161, 0, 50, 50));
    }
    else if (direction == 'w')
    {
        rect.setTextureRect(sf::IntRect(52, 0, 50, 50));
    }
};