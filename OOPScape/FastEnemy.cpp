#include "FastEnemy.h"

FastEnemy::FastEnemy()
    :Enemy()
{
}

FastEnemy::FastEnemy(const Point& position)
    :Enemy(position)
{
}

char FastEnemy::getSymbol() const
{
    return 'X';
}
