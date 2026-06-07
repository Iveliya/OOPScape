#include "Game.h"
#include <iostream>

void Game::initializeEnemies()
{
    enemies.clear();

    const std::vector<Point>& enemyPositions = board.getEnemyPositions();

    for (const Point& position : enemyPositions)
    {
        enemies.push_back(Enemy(position));
    }
}

void Game::printGameState() const
{
    std::vector<std::string> displayMaze = board.getMaze();

    Point heroPosition = hero.getPosition();

    displayMaze[heroPosition.y][heroPosition.x] = hero.getSymbol();

    for (const Enemy& enemy : enemies)
    {
        Point enemyPosition = enemy.getPosition();

        displayMaze[enemyPosition.y][enemyPosition.x] = enemy.getSymbol();
    }

    for (const std::string& row : displayMaze)
    {
        std::cout << row << std::endl;
    }
}

void Game::processCommand(char command)
{
}

void Game::moveHeroTo(const Point& newPosition)
{
}

bool Game::checkWin() const
{
    return false;
}

bool Game::checkLoss() const
{
    return false;
}

Game::Game()
{
    isGameOver = false;
    isWin = false;
}

bool Game::loadLevel(const std::string& filename)
{
    if (!board.loadFromFile(filename))
    {
        return false;
    }

    hero.setPosition(board.getStartPosition());

    initializeEnemies();

    isGameOver = false;
    isWin = false;

    return true;
}

void Game::run()
{
    while (!isGameOver)
    {
        printGameState();

        char command;
        std::cout << "Enter command: ";
        std::cin >> command;

        processCommand(command);
    }
}
