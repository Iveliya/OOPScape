#include "Board.h"
#include <fstream>
#include <iostream>

bool Board::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout<< "Error: Could not open level file." << std::endl;
        return false;
    }
    int size;
    file >> size;

    if (size < 2 || size>64) {
        std::cout << "Error: Invalid board size." << std::endl;
        return false;
    }

    file.ignore();
    file.clear();
    enemyPositions.clear();

    int startCount = 0;
    int finishCount = 0;
    for (int row = 0; row < size; row++)
    {
        std::string line;
        std::getline(file, line);
        if (line.length() != size) {
            std::cout << "Error: Invalid row length." << std::endl;
            return false;
        }
        for (int col = 0; col < size; col++)
        {
            char symbol = line[col];
            if (symbol != '*' && symbol != ' ' && symbol != 'S' && symbol != 'F' && symbol != 'E')
            {
                std::cout << "Error: Invalid symbol in level file." << std::endl;
                return false;
            }

            if (symbol == 'S')
            {
                startPosition = { col, row };
                startCount++;
            }
            else if (symbol == 'F')
            {
                finishPosition = { col, row };
                finishCount++;
            }
            else if (symbol == 'E')
            {
                enemyPositions.push_back({ col, row });
                line[col] = ' ';
            }
        }
        maze.push_back(line);
    }

    std::string extraLine;
    if (std::getline(file, extraLine))
    {
        std::cout << "Error: Too many rows in level file." << std::endl;
        return false;
    }

    if (startCount != 1)
    {
        std::cout << "Error: Level must contain exactly one start position." << std::endl;
        return false;
    }

    if (finishCount != 1)
    {
        std::cout << "Error: Level must contain exactly one finish position." << std::endl;
        return false;
    }

    return true;
}

void Board::print() const
{
    for (const std::string& row:maze)
    {
        std::cout << row << std::endl;
    }
}

bool Board::isWalkable(int x, int y) const
{
    int size = getSize();

    if (x < 0 || x >= size || y < 0 || y >= size)
    {
        return false;
    }

    return maze[y][x] != '*';
}

int Board::getSize() const
{
    return maze.size();
}

Point Board::getStartPosition() const
{
    return startPosition;
}

Point Board::getFinishPosition() const
{
    return finishPosition;
}

const std::vector<Point>& Board::getEnemyPositions() const
{
    return enemyPositions;
}

const std::vector<std::string>& Board::getMaze() const
{
    return maze;
}
