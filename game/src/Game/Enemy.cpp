#include "Enemy.h"

void Enemy::InitEnemy(float x, float y) {
    enemyRect = { x, y, 40, 40 };  // Setting enemy size
    type = Enemy1;  // Example enemy type
    isAlive = true;
}

void Enemy::UpdateEnemy(float deltaTime) {
    // Logic for enemy movement or behavior
}

void Enemy::DrawEnemy() {
    if (isAlive) {
        DrawRectangleRec(enemyRect, RED);  // Placeholder drawing for enemy
    }
}