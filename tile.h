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

        void initTile(int x, int y, int height);

    private:
        sf::ConvexShape diamond;
        bool obstruct;
        bool visObstruct;

};

#endif