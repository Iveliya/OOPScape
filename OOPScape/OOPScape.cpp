// OOPScape.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Board.h"

int main()
{
    Board board;

    if (!board.loadFromFile("levels/level1.txt"))
    {
        return 1;
    }

    board.print();

    return 0;
}

