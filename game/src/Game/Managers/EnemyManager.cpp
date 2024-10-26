#include "EnemyManager.h"
#include "Proyectil.h"
#include "raylib.h"
#include "GameManager.h"

EnemyManager::EnemyManager() {
	InitEnemies();
}

//Enemy type/draw logic
void EnemyManager::InitEnemies() {

	//textures
	enemy1 = LoadTexture("resources/Game/Enemy1.png");
	enemy2 = LoadTexture("resources/Game/Enemy2.png");
	enemy3 = LoadTexture("resources/Game/Enemy3.png");
	enemy4 = LoadTexture("resources/Game/Enemy4.png");

	for (int row = 0; row < ROW; row++) {
		for (int col = 0; col < COL; col++) {
			enemies[row][col].InitEnemy(((GetScreenWidth() - COL * 40) / 2) + col * 40, row * 40 + 100);
			if (row == 0) enemies[row][col].SetType(Enemy1);
			else if (row == 1) enemies[row][col].SetType(Enemy2);
			else if (row == 2) enemies[row][col].SetType(Enemy3);
			else enemies[row][col].SetType(Enemy4);
		}
	}

	enemySpeed = 50.0f;
	movingRight = true; //start mooving right
	landscapeW = 600.f; //to calculate de background limits

	//enemy bullets
	for (int i = 0; i < MAX_PROYECTILES; i++)
	{
		pjProyectiles[i].InitProyectil(0, 0, 3.f, 13.f, 100.f, false, -1);
		pjProyectiles[i].SetLanzado(false);
	}
	randomNum = GetRandomValue(0, 6);
}


void EnemyManager::UpdateEnemies(float deltaTime) {

	//Enemyes movement
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

	// Check limits and change direction
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

	//bullets
	//Enemies shoot whith random logic
	randomNum--;
	if (randomNum > 80) {
		randomNum = GetRandomValue(30, 110);  // restart counter

		int randomRow = GetRandomValue(0, ROW - 1);
		int randomCol = GetRandomValue(0, COL - 1);

		// Be sure that de shooter is alive and define de position of the bullet
		if (enemies[randomRow][randomCol].IsAlive()) {
			float posx = enemies[randomRow][randomCol].GetX() + (enemies[randomRow][randomCol].GetRectangle().width / 2) - 1.5f;
			float posy = enemies[randomRow][randomCol].GetY() + enemies[randomRow][randomCol].GetRectangle().height;

			LanzarProyectiles(posx, posy);
		}		
	}
	else if (GetRandomValue(0, 10) > 9) {
		randomNum = GetRandomValue(30, 110);  // restart counter
	}

	// Update bullets if they are shooted
	for (int i = 0; i < MAX_PROYECTILES; i++) {
		if (pjProyectiles[i].IsLanzado()) {
			pjProyectiles[i].UpdateProyectil(deltaTime);
		}
	}
}

//Draw enemies, theit bullets and the score convoy information
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

	//Bullets
	for (int i = 0; i < MAX_PROYECTILES; i++)
	{
		if (pjProyectiles[i].IsLanzado()) {
			pjProyectiles[i].DrawProyectil();
		}
	}

	//Score convoy information
	Font font = GameManager::GetGameManager().GetArcadeFont();

	DrawTextEx(font, "SCORE ADVANCE TABLE", Vector2{ 50, 300 }, 20, 1, WHITE);
	DrawTextEx(font, "CONVOY", Vector2{ 125, 300 + 30 }, 20, 1, BLUE);

	Texture2D enemyTextures[4] = { enemy1, enemy2, enemy3, enemy4 };
	int scores[4] = { 60, 50, 40, 30 };

	for (int i = 0; i < 4; i++) {
		DrawTextureEx(enemyTextures[i], Vector2{ 125, 350.f + (i * 40) }, 0.0f, 1.0f, WHITE);
		DrawText(TextFormat("%d", scores[i]), 165, 360.f + (i * 40), 20, BLUE);
	}
}

void EnemyManager::LanzarProyectiles(float posx, float posy) {
	for (int i = 0; i < MAX_PROYECTILES; i++)
	{
		if (!pjProyectiles[i].IsLanzado())
		{
			pjProyectiles[i].Launcher(posx, posy);
			pjProyectiles[i].SetLanzado(true);
			break;
		}
	}

}

void EnemyManager::SetScore(int row, int col) {
	int plus = 0;
	switch (enemies[row][col].GetType()) {
	case Enemy1:
		plus = 60;
		break;
	case Enemy2:
		plus = 50;
		break;
	case Enemy3:
		plus = 40;
		break;
	case Enemy4:
		plus = 30;
		break;
	}

	//calculate the total score
	GameManager::GetGameManager().SetScore(GameManager::GetGameManager().GetScore() + plus);
}

//Detect when a player bullet hit a alive enemy and desactivate both
bool EnemyManager::CheckCollisionWithProjectile(Proyectil& proyectil) {
	// Implementar lógica para verificar si un proyectil ha colisionado con un enemigo
	for (int row = 0; row < ROW; row++) {
		for (int col = 0; col < COL; col++) {
			if (enemies[row][col].IsAlive() && CheckCollisionRecs(enemies[row][col].GetRectangle(), proyectil.GetRectangle())) {
				enemies[row][col].SetAlive(false);
				SetScore(row, col);
				proyectil.Deactivate();
				return true;
			}
		}
	}
	return false;
}

//Detect when a enemy bullet hit the player and desactivate the first
bool EnemyManager::CheckCollisionWithPlayer(Vector2 playerPos, Vector2 playerSize) {
	Rectangle playerRect = { playerPos.x, playerPos.y, playerSize.x, playerSize.y };
	for (auto& proyectil : pjProyectiles) {
		if (proyectil.IsLanzado() && CheckCollisionRecs(playerRect, proyectil.GetRectangle())) {
			proyectil.Deactivate();
			return true;
		}
	}
	return false;
}
void EnemyManager::UnloadEnemies() {
	UnloadTexture(enemy1);
	UnloadTexture(enemy2);
	UnloadTexture(enemy3);
	UnloadTexture(enemy4);
}
