#pragma once
#include "Enemy.h"

class FastEnemy:public Enemy
{
public:
    FastEnemy();
    FastEnemy(const Point& position);

    char getSymbol() const override;
};

