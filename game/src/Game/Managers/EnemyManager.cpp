#include "EnemyManager.h"
#include "raylib.h"

EnemyManager::EnemyManager() {
    InitEnemies();
}

void EnemyManager::InitEnemies() {
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            enemies[row][col].InitEnemy(col * 60 + 50, row * 50 + 50);  // Positioning the enemies in grid
        }
    }
}

void EnemyManager::UpdateEnemies(float deltaTime) {
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            enemies[row][col].UpdateEnemy(deltaTime);
        }
    }
}

void EnemyManager::DrawEnemies() {
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            enemies[row][col].DrawEnemy();
        }
    }
}
