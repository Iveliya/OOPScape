#pragma once
#include "Hero.h"
#include "Board.h"

class Wizard:public Hero
{
public:
    Wizard();
    Wizard(const Point& position);

    char getSymbol() const override;

    bool teleport(const Board& board);
    bool useAbility(const Board& board) override;
};

