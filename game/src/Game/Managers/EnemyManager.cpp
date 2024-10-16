#include "EnemyManager.h"
#include "Proyectil.h"
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

	//proyectiles de enemigos
	for (int i = 0; i < MAX_PROYECTILES; i++)
	{
		pjProyectiles[i].InitProyectil(0,0,3.f,13.f, 100.f, false, -1);
		pjProyectiles[i].SetLanzado(false);
	}
	randomNum = GetRandomValue(0, 6);
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

	//proyectiles

	if (randomNum > 0) {
		randomNum = 0;  // Reiniciar el contador
		int randomRow = GetRandomValue(0, ROW - 1);
		int randomCol = GetRandomValue(0, COL - 1);

		// Asegurarse de que el enemigo seleccionado está vivo antes de disparar
		if (enemies[randomRow][randomCol].IsAlive()) {
			float posx = enemies[randomRow][randomCol].GetX() + (enemies[randomRow][randomCol].GetRectangle().width / 2) - 1.5f;
			float posy = enemies[randomRow][randomCol].GetY() + enemies[randomRow][randomCol].GetRectangle().height;

			LanzarProyectiles(posx, posy);
		}
		// Reiniciar aleatoriedad para el siguiente disparo
		randomNum = GetRandomValue(0, 1);
	}

	// Actualizar los proyectiles de los enemigos
	for (int i = 0; i < MAX_PROYECTILES; i++) {
		if (pjProyectiles[i].IsLanzado()) {
			pjProyectiles[i].UpdateProyectil(deltaTime);
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

	//proyectiles
	for (int i = 0; i < MAX_PROYECTILES; i++)
	{
		if (pjProyectiles[i].IsLanzado()) {
			pjProyectiles[i].DrawProyectil();
		}
	}
}

void EnemyManager::LanzarProyectiles(float posx, float posy)
{
	for (int i = 0; i < MAX_PROYECTILES; i++)
	{
		if (!pjProyectiles[i].IsLanzado())
		{
			pjProyectiles[i].Launcher(posx, posy);  
			pjProyectiles[i].SetLanzado(true);
			pjProyectiles[i].SetLanzado(true);
			break;
		}
	}

}