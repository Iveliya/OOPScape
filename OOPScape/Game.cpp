#include "Game.h"
#include <iostream>
#include <queue>
#include "Wizard.h"
#include "Knight.h"

void Game::chooseHero()
{
    int choice;

    std::cout << "Choose hero:" << std::endl;
    std::cout << "1. Wizard" << std::endl;
    std::cout << "2. Knight" << std::endl;
    std::cout << "Choice: ";

    std::cin >> choice;

    if (choice == 1)
    {
        hero = std::make_unique<Wizard>();
    }
	else if (choice == 2)
    {
        hero = std::make_unique<Knight>();
    }
    else {
		std::cout << "Invalid hero choice!"<<std::endl;
    }
}

void Game::initializeEnemies()
{
    enemies.clear();

    const std::vector<Point>& enemyPositions = board.getEnemyPositions();

    for (int i = 0; i < enemyPositions.size(); i++)
    {
        if (i % 2 == 0)
        {
            enemies.push_back(std::make_unique<Enemy>(enemyPositions[i]));
        }
        else
        {
            enemies.push_back(std::make_unique<FastEnemy>(enemyPositions[i]));
        }
    }
}

void Game::printGameState() const
{
    std::vector<std::string> displayMaze = board.getMaze();

    for (const std::unique_ptr<Enemy>& enemy : enemies)
    {
        Point enemyPosition = enemy->getPosition();
        displayMaze[enemyPosition.y][enemyPosition.x] = enemy->getSymbol();
    }

    Point heroPosition = hero->getPosition();
    displayMaze[heroPosition.y][heroPosition.x] = hero->getSymbol();

    for (const std::string& row : displayMaze)
    {
        std::cout << row << std::endl;
    }
}

void Game::processCommand(const std::string& command)
{
    if (command == "OOP" || command == "oop")
    {

        if (hero->isKnight())
        {
            if (attackEnemyNearHero())
            {
                std::cout << "Enemy defeated!" << std::endl;
            }
            else
            {
                std::cout << "No enemy nearby!" << std::endl;
            }

            return;
        }

        std::string direction;

        std::cout << "Enter teleport direction (L/R/U/D): ";
        std::cin >> direction;

        if (hero->useAbility(board, direction))
        {
            std::cout << "Ability used successfully!" << std::endl;
        }
        else
        {
            std::cout << "Ability failed!" << std::endl;
        }

        moveEnemies();

        if (checkLoss())
        {
            isGameOver = true;
            isWin = false;
        }

        return;
        
    }

    Point currentPosition = hero->getPosition();
    Point newPosition = currentPosition;

    if (command == "L" || command == "l")
    {
        newPosition.x--;
    }
    else if (command == "R" || command == "r")
    {
        newPosition.x++;
    }
    else if (command == "U" || command == "u")
    {
        newPosition.y--;
    }
    else if (command == "D" || command == "d")
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
        return;
    }

    if (checkLoss())
    {
        isGameOver = true;
        isWin = false;
        return;
    }

    moveEnemies();

    if (checkLoss())
    {
        isGameOver = true;
        isWin = false;
    }

}

void Game::moveHeroTo(const Point& newPosition)
{
    if (board.isWalkable(newPosition.x, newPosition.y))
    {
        hero->setPosition(newPosition);
    }
    else
    {
        std::cout << "You cannot move there!" << std::endl;
    }
}
bool tryMoveTowardsHeroBFS(Point& enemyPosition, const Point& heroPosition, const Board& board)
{
    int n = board.getSize();
    int width = n;

    std::vector<int> parent(width * width, -1);
    std::queue<Point> queue;

    int start = enemyPosition.y * width + enemyPosition.x;
    int goal = heroPosition.y * width + heroPosition.x;

    parent[start] = start;
    queue.push(enemyPosition);

    const int dx[4] = { -1, 1, 0, 0 };
    const int dy[4] = { 0, 0, -1, 1 };

    bool found = false;

    while (!queue.empty())
    {
        Point current = queue.front();
        queue.pop();

        int currentIndex = current.y * width + current.x;

        if (currentIndex == goal)
        {
            found = true;
            break;
        }

        for (int i = 0; i < 4; i++)
        {
            int nextX = current.x + dx[i];
            int nextY = current.y + dy[i];

            if (!board.isWalkable(nextX, nextY))
            {
                continue;
            }

            int nextIndex = nextY * width + nextX;

            if (parent[nextIndex] != -1)
            {
                continue;
            }

            parent[nextIndex] = currentIndex;
            queue.push(Point{ nextX, nextY });
        }
    }

    if (!found)
    {
        return false;
    }

    int current = goal;

    while (parent[current] != start && current != start)
    {
        current = parent[current];
    }

    if (current == start)
    {
        return false;
    }

    enemyPosition.x = current % width;
    enemyPosition.y = current / width;

    return true;
}

void Game::moveEnemies()
{
    Point heroPosition = hero->getPosition();

    for (std::unique_ptr<Enemy>& enemy : enemies)
    {
        int steps = enemy->getMoveCount();

        for (int i = 0; i < steps; i++)
        {
            Point enemyPosition = enemy->getPosition();

            if (tryMoveTowardsHeroBFS(enemyPosition, heroPosition, board))
            {
                enemy->setPosition(enemyPosition);
            }

            if (checkLoss())
            {
                return;
            }
        }
    }
}

int Game::calculateDistance(int first, int second) const
{
    if (first > second)
    {
        return first - second;
    }

    return second - first;
}

bool Game::attackEnemyNearHero()
{
    Point heroPosition = hero->getPosition();

    for (auto it = enemies.begin(); it != enemies.end(); ++it)
    {
        Point enemyPosition = (*it)->getPosition();

        int dx = calculateDistance(heroPosition.x, enemyPosition.x);
        int dy = calculateDistance(heroPosition.y, enemyPosition.y);

        if ((dx == 1 && dy == 0) || (dx == 0 && dy == 1))
        {
            enemies.erase(it);
            return true;
        }
    }

    return false;
}

bool Game::checkWin() const
{
    return hero->getPosition().x == board.getFinishPosition().x
        && hero->getPosition().y == board.getFinishPosition().y;
}

bool Game::checkLoss() const
{
    Point heroPosition = hero->getPosition();
    for (const std::unique_ptr<Enemy>& enemy : enemies)
    {
        Point enemyPosition = enemy->getPosition();

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
    chooseHero();
    isGameOver = false;
    isWin = false;
}

bool Game::loadLevel(const std::string& filename)
{
    if (!board.loadFromFile(filename))
    {
        return false;
    }

    hero->setPosition(board.getStartPosition());

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

        std::string command;
		std::cout << "Enter command (L/R/U/D for movement, OOP for ability): ";
        std::cin >> command;
		if (command != "L" && command != "R" && command != "U" && command != "D" && command != "OOP" &&
			command != "l" && command != "r" && command != "u" && command != "d" && command != "oop")
		{
			std::cout << "Invalid command!" << std::endl;
			continue;
		}
        else {
            processCommand(command);
        }
    }

    std::cout << std::endl;
    std::cout << "Final board state:" << std::endl;
    printGameState();

    if (isWin)
    {
        std::cout << "You win!" << std::endl;
    }
    else
    {
        std::cout << "You lose!" << std::endl;
    }
}

