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
    bool DetectarColisiones(Rectangle proyectil);
private:
    //texturas
    Texture2D enemy1;
    Texture2D enemy2;
    Texture2D enemy3;
    Texture2D enemy4;


    std::array<std::array<Enemy, COL>, ROW> enemies;

    float enemySpeed = 0.f;
    bool movingRight = true;
    float landscapeW = 600.f;
};
