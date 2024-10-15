#include "EnemyManager.h"
#include "raylib.h"

EnemyManager::EnemyManager() {
	InitEnemies();

}

void EnemyManager::InitEnemies() {
	for (int row = 0; row < ROW; row++) {
		for (int col = 0; col < COL; col++) {
			enemies[row][col].InitEnemy(((GetScreenWidth() - COL * 40) / 2) + col * 40, row * 40 + 100);  // Posicionar enemigos
			if (row == 0) enemies[row][col].SetType(Enemy1);
			else if (row == 1) enemies[row][col].SetType(Enemy2);
			else if (row == 2) enemies[row][col].SetType(Enemy3);
			else enemies[row][col].SetType(Enemy4);  // Resto de filas con Enemy4
		}
	}
	enemy1 = LoadTexture("resources/Game/Enemy1.png");
	enemy2 = LoadTexture("resources/Game/Enemy2.png");
	enemy3 = LoadTexture("resources/Game/Enemy3.png");
	enemy4 = LoadTexture("resources/Game/Enemy4.png");
	enemySpeed = 50.0f;
	movingRight = true;
	landscapeW = 600.f;
}

void EnemyManager::UpdateEnemies(float deltaTime) {



	for (int row = 0; row < ROW; row++) 
	{
		for (int col = 0; col < COL; col++)
		{
			if (movingRight) 
			{
				enemies[row][col].MoveEnemy(enemySpeed * deltaTime, 0);

			}
			else 
			{

				enemies[row][col].MoveEnemy(-enemySpeed * deltaTime, 0);

			}
			/*if (enemies[row][col].IsAlive() && CheckCollisionRecs(enemies[row][col].GetRectangle(), proyectil))
			{
				enemies[row][col].SetAlive(false);
				DrawEnemies();
			}*/
		}
	}

	// Comprobar si el bloque toca los bordes y cambiar de dirección
	
	for (int col = 0; col < COL; col++) {
		if (movingRight && enemies[0][col].GetX() + 40 >= (GetScreenWidth() / 2) + (landscapeW / 2)) {
			movingRight = false;
			break;
		}
		else if (!movingRight && enemies[0][col].GetX() <= (GetScreenWidth() / 2) - (landscapeW / 2)) {
			movingRight = true;
			break;
		}
	}
}
bool EnemyManager::DetectarColisiones(Rectangle proyectil)
{
	//detectar colisiones con proyectiles

	for (int row = 0; row < ROW; row++)
	{
		for (int col = 0; col < COL; col++)
		{			
			if (enemies[row][col].IsAlive() && CheckCollisionRecs(enemies[row][col].GetRectangle(), proyectil))
			{
				enemies[row][col].SetAlive(false);
				return false; //elimina el proyectil
				//DrawEnemies();
			}
		}
	}
	return true; //proyectil continua
}
void EnemyManager::DrawEnemies() {
	for (int row = 0; row < ROW; row++) {
		for (int col = 0; col < COL; col++) {
			EnemyType type = enemies[row][col].GetType();
			if (!enemies[row][col].IsAlive()) continue;
			if (type == Enemy1 && (col == 3 || col == 6)) {
				DrawTexture(enemy1, enemies[row][col].GetX(), enemies[row][col].GetY(), WHITE);
			}
			else if (type == Enemy2 && col >= 2 && col <= 7) {
				DrawTexture(enemy2, enemies[row][col].GetX(), enemies[row][col].GetY(), WHITE);
			}
			else if (type == Enemy3 && col != 0 && col != 9) {
				DrawTexture(enemy3, enemies[row][col].GetX(), enemies[row][col].GetY(), WHITE);
			}
			else if (type == Enemy4) {
				DrawTexture(enemy4, enemies[row][col].GetX(), enemies[row][col].GetY(), WHITE);
			}
		}
	}
}