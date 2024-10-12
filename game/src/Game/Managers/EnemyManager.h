#pragma once
//#include "Enemy.h"
#include "Game/Enemy.h"
#include <array>
#define ROW 6
#define COL 10

class EnemyManager {
public:
    EnemyManager();
    void InitEnemies();
    void UpdateEnemies(float deltaTime);
    void DrawEnemies();

private:
    //texturas
    Texture2D enemy1;
    Texture2D enemy2;
    Texture2D enemy3;
    Texture2D enemy4;


    std::array<std::array<Enemy, COL>, ROW> enemies;
};
