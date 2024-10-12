#include "EnemyManager.h"
#include "raylib.h"

EnemyManager::EnemyManager() {
    InitEnemies();
    
}

void EnemyManager::InitEnemies() {
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            // Alterna el tipo de enemigo basado en la posición (por ejemplo)
            if (row == 0) {
                enemies[row][col].SetType(Enemy1);
            }
            else if (row == 1) {
                enemies[row][col].SetType(Enemy2);
            }
            else {
                enemies[row][col].SetType(Enemy3);
            }
            enemies[row][col].InitEnemy(col * 60 + 50, row * 50 + 50);
        }
    }
    enemy1 = LoadTexture("resources/Game/Enemy1.png");
    enemy2 = LoadTexture("resources/Game/Enemy2.png");
    enemy3 = LoadTexture("resources/Game/Enemy3.png");
    enemy4 = LoadTexture("resources/Game/Enemy4.png");
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
            EnemyType type = enemies[row][col].GetType();

            if (type == Enemy1) {
                DrawTexture(enemy1, enemies[row][col].GetX(), enemies[row][col].GetY(), WHITE);
            }
            else if (type == Enemy2) {
                DrawTexture(enemy2, enemies[row][col].GetX(), enemies[row][col].GetY(), WHITE);
            }
            else if (type == Enemy3) {
                DrawTexture(enemy3, enemies[row][col].GetX(), enemies[row][col].GetY(), WHITE);
            }
            else if (type == Enemy4) {
                DrawTexture(enemy4, enemies[row][col].GetX(), enemies[row][col].GetY(), WHITE);
            }
        }
    }
}
