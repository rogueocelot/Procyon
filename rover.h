#ifndef ROVERH
#define ROVERH

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class Rover
{
    public:
        Rover();

        Rover(int height, int width);

        sf::RectangleShape getRect(){return rect;}

        int getGridX(){return gridX;}
        int getGridY(){return gridY;}

        int getCurrentX(){return currentX;}
        int getCurrentY(){return currentY;}

        void initRect(int x, int y, int size);
        void rectPosition(int x, int y);
        void gridPosition(int x, int y);

        void setText(sf::Texture &texture, char direction);

    private:
        sf::RectangleShape rect;
        sf::Vector2f rectSize;
        sf::Texture texture;
        int height;
        int width;

        int gridX;
        int gridY;

        int currentX;
        int currentY;


};

#endif