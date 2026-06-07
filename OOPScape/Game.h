#pragma once
#include "Board.h"
#include "Hero.h"
#include "Enemy.h"
class Game
{
private:
    Board board;
    Hero hero;
    std::vector<Enemy> enemies;

    bool isGameOver;
    bool isWin;

    void initializeEnemies();
    void printGameState() const;

    void processCommand(char command);
    void moveHeroTo(const Point& newPosition);

    bool checkWin() const;
    bool checkLoss() const;
public:
    Game();

    bool loadLevel(const std::string& filename);
    void run();

};

