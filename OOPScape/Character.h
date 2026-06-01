#pragma once
#include "Point.h"
class Character
{
protected:
    Point position;

public:
    Character();
    Character(const Point& position);

    virtual ~Character() = default;

    Point getPosition() const;
    void setPosition(const Point& position);

    virtual char getSymbol() const = 0;
};

