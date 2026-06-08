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

    void initializeEnemies();
    void printGameState() const;

    void processCommand(const std::string& command);
    void moveHeroTo(const Point& newPosition);

    void moveEnemies();

    bool checkWin() const;
    bool checkLoss() const;
public:
    Game();

    bool loadLevel(const std::string& filename);
    void run();

};

