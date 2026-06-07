// OOPScape.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Board.h"
#include "Game.h"

int main()
{
    Game game;

    if (!game.loadLevel("levels/level1.txt"))
    {
        return 1;
    }

    game.run();

    return 0;
}

