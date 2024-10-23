
#pragma once

#include "ScreenGameplay.h"
#include "raylib.h"
#include "../Game/Player.h"
#include "Game/Managers/GameManager.h"
#include "Game/GlobalGameDefines.h"
#include "../Game/Proyectil.h"

#include <string>

Player player;



ScreenGameplayState::ScreenGameplayState()
{

}

ScreenGameplayState& ScreenGameplayState::getInstance()
{
	static ScreenGameplayState singleton;
	return singleton;
}

void ScreenGameplayState::InitScreen(void)
{
	framesCounter = 0;
	finishScreen = 0;

	//TEXTURAS
	landscape = LoadTexture("resources/Game/Landscape.png");
	//player = LoadTexture("resources/Game/Player.png");

	 // Inicializar player
	Vector2 screenSize = { (float)GetScreenWidth(), (float)GetScreenHeight() };
	player.Init(screenSize);

	// Inicializar enemigos
	enemyManager.InitEnemies();

}

void ScreenGameplayState::UpdateScreen(float deltaTime)
{
	EvaluateInput();
	framesCounter++;

	// GAMEPLAY
	player.Update(deltaTime, landscape);

	// Actualizar enemigos
	enemyManager.UpdateEnemies(deltaTime);

	// Detectar colisiones entre los proyectiles del jugador y los enemigos
	for (int i = 0; i < MAX_PROYECTILES; i++) {
		if (player.GetProyectil(i).IsLanzado()) {
			enemyManager.CheckCollisionWithProjectile(player.GetProyectil(i));
		}
	}

	// Verificar si el jugador ha sido golpeado
	if (enemyManager.CheckCollisionWithPlayer(player.GetPosition(), player.GetSize())) {
		player.DecreaseLife();
		if (player.GetLives() <= 0) {
			finishScreen = 4; // END SCREEN
		}
	}
}

void ScreenGameplayState::DrawScreen(void)
{

	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
	DrawTexture(landscape, (GetScreenWidth() - (landscape.width)) / 2, (GetScreenHeight() - landscape.height) / 4, WHITE);

	//Player
	player.Draw();

	// Dibujar enemigos
	enemyManager.DrawEnemies();

	GameManager& GameInst = GameManager::GetGameManager();

	// UI Score, lives

	Font font = GameInst.GetArcadeFont();

	//DrawTextEX(font,"SCORE:", 300.f, 100.f, 25, WHITE);
	float textWidth = MeasureTextEx(GameInst.GetArcadeFont(), "Press 'O' for Instructions", 25, 3).x;
	float posx = (275) - (textWidth / 2.f);
	DrawTextEx(font, "SCORE:", Vector2{ posx, 100.f }, 25, 3, WHITE);
	DrawText(to_string(GameInst.GetScore()).c_str(), 440.f, 100.f, 25, WHITE);
}


void ScreenGameplayState::UnloadScreen(void)
{
	UnloadTexture(landscape);
	//UnloadTexture(player);
	player.Unload();
}

int  ScreenGameplayState::FinishScreen(void)
{
	return finishScreen;
}

void ScreenGameplayState::EvaluateInput()
{

	if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
	{
		finishScreen = 4;   // END SCREEN
	}
}

void ScreenGameplayState::DebugOptions()
{

}

void ScreenGameplayState::DrawDebug()
{
	GameManager& GameInst = GameManager::GetGameManager();

}