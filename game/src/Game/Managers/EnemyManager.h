#pragma once
#include "Enemy.h"
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
    std::array<std::array<Enemy, COL>, ROW> enemies;
};
