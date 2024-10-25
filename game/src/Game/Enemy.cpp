#include "Enemy.h"

void Enemy::InitEnemy(float x, float y) {
	enemyRect = { x, y, 40, 40 };
	type = Enemy1;
	isAlive = true;
}

//there's no need for update function in this class

void Enemy::DrawEnemy() {
	if (isAlive) {
		DrawRectangleRec(enemyRect, RED);  // Placeholder drawing for enemy
	}
}

void Enemy::SetType(EnemyType type) {
	this->type = type;
}

EnemyType Enemy::GetType() const {
	return type;
}

float Enemy::GetX() const {
	return enemyRect.x;
}

float Enemy::GetY() const {
	return enemyRect.y;
}

//Movement logic
void Enemy::MoveEnemy(float dirX, float dirY) {
	enemyRect.x += dirX;
	enemyRect.y += dirY;
}

bool Enemy::IsAlive() const{
	return isAlive;
}
void Enemy::SetAlive(bool alive) {
	isAlive = alive;

}

//Take de rect representation of the enemy (to detect collisions)
Rectangle Enemy::GetRectangle() const {
	return enemyRect;
}