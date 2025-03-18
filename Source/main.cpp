#include "Game.h"


int main()
{
    Game gameInstance;
    while (gameInstance.isWindowOpen())
    {
        gameInstance.update();
        gameInstance.render();
    }

    return 0;
}