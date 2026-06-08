#pragma once
#include "Character.h"
class Enemy:public Character
{
public:
    Enemy();
    Enemy(const Point& position);

    virtual ~Enemy() = default;

    char getSymbol() const override;

};

