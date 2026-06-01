#pragma once
#include "Character.h"
class Enemy:public Character
{
public:
    Enemy();
    Enemy(const Point& position);

    char getSymbol() const override;

};

