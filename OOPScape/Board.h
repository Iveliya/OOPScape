#pragma once
#include <vector>
#include <string>
#include "Point.h"
class Board
{
private:
    std::vector<std::string> maze;

    Point startPosition;
    Point finishPosition;

    std::vector<Point> enemyPositions;

public:
    bool loadFromFile(const std::string& filename);

    void print() const;

    bool isWalkable(int x, int y) const;

    int getSize() const;

    Point getStartPosition() const;
    Point getFinishPosition() const;

    const std::vector<Point>& getEnemyPositions() const;
    const std::vector<std::string>& getMaze() const;
};

