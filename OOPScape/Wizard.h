#pragma once
#include <string>
#include "Hero.h"
#include "Board.h"

class Wizard:public Hero
{
public:
    Wizard();
    Wizard(const Point& position);

    char getSymbol() const override;

    bool teleport(const Board& board, const std::string& direction);
    bool useAbility(const Board& board, const std::string& direction) override;
};

