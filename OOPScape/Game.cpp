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
    Point currentPosition = hero.getPosition();
    Point newPosition = currentPosition;

    if (command == 'L' || command == 'l')
    {
        newPosition.x--;
    }
    else if (command == 'R' || command == 'r')
    {
        newPosition.x++;
    }
    else if (command == 'U' || command == 'u')
    {
        newPosition.y--;
    }
    else if (command == 'D' || command == 'd')
    {
        newPosition.y++;
    }
    else
    {
        std::cout << "Invalid command!" << std::endl;
        return;
    }

    moveHeroTo(newPosition);

    if (checkWin())
    {
        isGameOver = true;
        isWin = true;
    }
    else if (checkLoss())
    {
        isGameOver = true;
        isWin = false;
    }

}

void Game::moveHeroTo(const Point& newPosition)
{
    if (board.isWalkable(newPosition.x, newPosition.y))
    {
        hero.setPosition(newPosition);
    }
    else
    {
        std::cout << "You cannot move there!" << std::endl;
    }
}

bool Game::checkWin() const
{
    return hero.getPosition().x == board.getFinishPosition().x
        && hero.getPosition().y == board.getFinishPosition().y;
}

bool Game::checkLoss() const
{
    Point heroPosition = hero.getPosition();
    for (const Enemy& e : enemies)
    {
        Point enemyPosition = e.getPosition();

        if (enemyPosition.x == heroPosition.x && 
            enemyPosition.y == heroPosition.y)
        {
            return true;
        }

    }
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

    if (isWin)
    {
        std::cout << "You win!" << std::endl;
    }
    else
    {
        std::cout << "You lose!" << std::endl;
    }
}

