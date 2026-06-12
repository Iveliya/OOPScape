#include "Knight.h"

Knight::Knight()
    :Hero()
{
}

Knight::Knight(const Point& position)
    :Hero(position)
{
}

char Knight::getSymbol() const
{
    return 'K';
}

bool Knight::isKnight() const
{
    return true;
}

bool Knight::useAbility(const Board& board, const std::string& direction)
{
    return false;
}
