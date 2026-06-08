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

bool Wizard::teleport(const Board& board)
{
    Point newPosition = position;

    newPosition.x += 2;

    if (board.isWalkable(newPosition.x, newPosition.y))
    {
        position = newPosition;
        return true;
    }

    return false;
}

bool Wizard::useAbility(const Board& board)
{
    return teleport(board);
}
