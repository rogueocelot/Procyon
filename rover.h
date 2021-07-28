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

        void initRect(int x, int y, int size);
        void rectPosition(int x, int y);

    private:
        sf::RectangleShape rect;
        sf::Vector2f rectSize;
        int height;
        int width;
        int gridX;
        int gridY;


};

#endif