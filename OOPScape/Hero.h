#pragma once
#include "Character.h"
#include "Board.h"
#include <string>

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

    virtual bool isKnight() const;
    virtual bool useAbility(const Board& board, const std::string& direction);
};

