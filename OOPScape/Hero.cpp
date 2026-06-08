#include "Hero.h"

Hero::Hero():Character()
{
}

Hero::Hero(const Point& position)
	:Character(position)
{
}

char Hero::getSymbol() const
{
	return 'H';
}

void Hero::moveLeft()
{
	position.x--;
}

void Hero::moveRight()
{
	position.x++;
}

void Hero::moveUp()
{
	position.y--;
}

void Hero::moveDown()
{
	position.y++;
}

bool Hero::useAbility(const Board& board)
{
	return false;
}
