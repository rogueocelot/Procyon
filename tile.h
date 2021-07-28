#ifndef TILEH
#define TILEH

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class Tile
{
    public:
        Tile();

        Tile(int x, int y, int height);

        sf::ConvexShape getGrid(){return diamond;}
        int getHeight(){return height;}
        int getX(){return x;}
        int getY(){return y;}

        void initTile(int x, int y, int height);
        void editColor();
        void resetColor();

    private:
        sf::ConvexShape diamond;
        int x;
        int y;
        int height;
        bool obstruct;
        bool visObstruct;

};

#endif