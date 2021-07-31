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
        sf::RectangleShape getRockShape(){return rockShape;}

        
        int getHeight(){return height;}
        bool getObstruct(){return obstruct;}
        int getX(){return x;}
        int getY(){return y;}
        bool getRocks(){return rocks;}

        void initTile(int x, int y, int height);
        void initTexture(sf::Texture &texture);

        void setRandom(sf::Texture &organic, sf::Texture &rockTexture);

        void setObstruct(bool val){obstruct = val;}

        void editColor();
        void resetColor();

    private:
        sf::ConvexShape diamond;
        sf::Texture texture;
        sf::RectangleShape rockShape;

        int x;
        int y;
        int height;
        bool obstruct;
        bool visObstruct;
        bool rocks;

};

#endif