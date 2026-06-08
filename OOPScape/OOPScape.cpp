// OOPScape.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Board.h"
#include "Game.h"

int main()
{
    int levelChoice;

    std::cout << "Choose level:" << std::endl;
    std::cout << "1. Level 1" << std::endl;
    std::cout << "2. Level 2" << std::endl;
    std::cout << "3. Level 3" << std::endl;
    std::cout << "4. Level 4" << std::endl;
    std::cout << "5. Level 5" << std::endl;
    std::cout << "6. Level 6" << std::endl;
    std::cout << "7. Level 7" << std::endl;
    std::cout << "8. Level 8" << std::endl;
    std::cout << "9. Level 9" << std::endl;
    std::cout << "10. Level 10" << std::endl;
    std::cout << "Choice: ";

    std::cin >> levelChoice;

    if (levelChoice < 1 || levelChoice > 10)
    {
        std::cout << "Invalid level choice!" << std::endl;
        return 1;
    }

    std::string levelFileName = "levels/level" + std::to_string(levelChoice) + ".txt";

    Game game;

    if (!game.loadLevel(levelFileName))
    {
        return 1;
    }

    game.run();

    return 0;
}

