#ifndef GAMEH
#define GAMEH

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <ctime>
#include <iostream>
#include <queue>
#include <list>
#include <string>
#include <sstream>

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
        void renderDig();
        void renderText();

        void moveRover();

        void Dig();

        //accessors
        const bool getStatus() const {return this->window->isOpen();}
    

    private:
        //variables
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event event;
        sf::View view;
        sf::View UI;

        //game variables
        int mouseDelta;
        float zoom;
        int roverSize;
        int tileNum;
        int science;
        //tracks if window is focused
        bool focus;
        int terrainSize;

        //text variables
        sf::Font font;
        sf::Text text;
        string dispScience;
        string dispNum;

        //movement variables
        bool move;
        int moveX;
        int moveY;
        int nextX;
        int nextY;
        char direction;
        bool ordering;
        bool searching;

        //digging variables
        bool digging;
        bool displayDig;
        int digCounter;
        sf::RectangleShape scienceRect;
        sf::Vector2f digSize;

        //move stuff
        struct Move{
            int x;
            int y;
            //Move *prev;
            int prev;
        };
        queue<Move> checking;
        vector<Move> checked;
        list<Move> path;
        Move tempMove;

        //game objects
        sf::ConvexShape boundsRect;
        vector<vector<Tile>> grid;
        Rover rover;

        //textures
        sf::Texture tileTexture;
        sf::Texture roverTexture;
        sf::Texture organicTexture;
        sf::Texture rockTexture;
        sf::Texture researchTexture;

        //mouse position
        sf::Vector2i mouseWindow;
        sf::Vector2f mousePosition;

        //private functions
        void initVariables();
        void initWindow();
        void initGrid();
        void initRover();
        void initText();

};

#endif