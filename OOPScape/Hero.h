#pragma once
#include "Character.h"

class Hero:public Character
{
public:
    Hero();
    Hero(const Point& position);

    char getSymbol() const override;

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
};

