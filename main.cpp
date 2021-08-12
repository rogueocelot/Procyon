#include "game.h"

using namespace std;

int main()
{
    //initialize random
    srand(time(NULL));

    Game game;

    //main game loop
    while(game.getStatus())
    {
        //update
        game.update();
        //render
        game.render();
    }
    //TODO
    //windows resizing
    //not diplaying every tile
    //only display some tiles
    //add status
    //add hazards
    //some kind of state system
    //UI


    return 0;
}