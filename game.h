#ifndef GAMEH
#define GAMEH

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <ctime>
#include <iostream>

#include "tile.h"
#include "rover.h"

using namespace std;

//game engine class
class Game
{
    public:
        //constructors / destructors
        Game();

        virtual ~Game();

        //engine stuff
        void update();
        void render();

        void pollEvents();
        void updateMousePos();
        void updateRover();

        void renderGrid();
        void renderRover();

        //accessors
        const bool getStatus() const {return this->window->isOpen();}
    

    private:
        //variables
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event event;
        sf::View view;

        //game variables
        int mouseDelta;
        float zoom;
        int roverSize;


        //game objects
        vector<vector<Tile>> grid;
        Rover rover;

        //mouse position
        sf::Vector2i mouseWindow;
        sf::Vector2f mousePosition;

        //private functions
        void initVariables();
        void initWindow();
        void initGrid();
        void initRover();
};

#endif