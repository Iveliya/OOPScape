#include "Wizard.h"

Wizard::Wizard()
    :Hero()
{
}

Wizard::Wizard(const Point& position)
    :Hero(position)
{
}

char Wizard::getSymbol() const
{
    return 'W';
}

bool Wizard::useAbility(const Board& board, const std::string& direction)
{
    return teleport(board, direction);
}

bool Wizard::teleport(const Board& board, const std::string& direction)
{
    Point newPosition = position;

    if (direction == "R" || direction == "r")
    {
        newPosition.x += 2;
    }
    else if (direction == "L" || direction == "l")
    {
        newPosition.x -= 2;
    }
    else if (direction == "U" || direction == "u")
    {
        newPosition.y -= 2;
    }
    else if (direction == "D" || direction == "d")
    {
        newPosition.y += 2;
    }
    else
    {
        return false;
    }

    if (board.isWalkable(newPosition.x, newPosition.y))
    {
        position = newPosition;
        return true;
    }

    return false;
}
