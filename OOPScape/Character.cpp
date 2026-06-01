#include "Character.h"

Character::Character()
{
    position = { 0,0 };
}

Character::Character(const Point& position)
    :position(position)
{
}

Point Character::getPosition() const
{
    return position;
}

void Character::setPosition(const Point& position)
{
    this->position = position;
}

