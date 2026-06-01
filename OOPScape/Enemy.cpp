#include "Enemy.h"

Enemy::Enemy():Character()
{
}

Enemy::Enemy(const Point& position)
    :Character(position)
{
}

char Enemy::getSymbol() const
{
    return 'E';
}
