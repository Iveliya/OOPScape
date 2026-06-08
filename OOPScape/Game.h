#pragma once
#include <memory>
#include "Board.h"
#include "Hero.h"
#include "Enemy.h"
class Game
{
private:
    Board board;
    std::unique_ptr<Hero> hero;
    std::vector<Enemy> enemies;

    bool isGameOver;
    bool isWin;

    void chooseHero();

    void initializeEnemies();
    void printGameState() const;

    void processCommand(const std::string& command);
    void moveHeroTo(const Point& newPosition);

    void moveEnemies();

    int calculateDistance(int first, int second) const;
    bool attackEnemyNearHero();

    bool checkWin() const;
    bool checkLoss() const;
public:
    Game();

    bool loadLevel(const std::string& filename);
    void run();

};

