#pragma once
#include "Hero.h"

class Knight:public Hero
{
public:
    Knight();
    Knight(const Point& position);

    char getSymbol() const override;

    bool isKnight() const override;
    bool useAbility(const Board& board, const std::string& direction) override;
};

