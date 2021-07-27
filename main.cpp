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


    return 0;
}