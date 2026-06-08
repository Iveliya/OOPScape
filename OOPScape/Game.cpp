#include "Game.h"
#include <iostream>
#include <queue>
#include "Wizard.h"

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

    for (const Enemy& enemy : enemies)
    {
        Point enemyPosition = enemy.getPosition();
        displayMaze[enemyPosition.y][enemyPosition.x] = enemy.getSymbol();
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

        if (checkWin())
        {
            isGameOver = true;
            isWin = true;
            return;
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

    for (Enemy& enemy : enemies)
    {
        Point enemyPosition = enemy.getPosition();

        if (tryMoveTowardsHeroBFS(enemyPosition, heroPosition, board))
        {
            enemy.setPosition(enemyPosition);
        }
    }
}

bool Game::checkWin() const
{
    return hero->getPosition().x == board.getFinishPosition().x
        && hero->getPosition().y == board.getFinishPosition().y;
}

bool Game::checkLoss() const
{
    Point heroPosition = hero->getPosition();
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
    hero = std::make_unique<Wizard>();
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

