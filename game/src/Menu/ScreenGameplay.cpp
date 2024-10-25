
#pragma once

#include "ScreenGameplay.h"
#include "raylib.h"
#include "../Game/Player.h"
#include "Game/Managers/GameManager.h"
#include "Game/GlobalGameDefines.h"
#include "../Game/Proyectil.h"

#include <string>

Player player; //Initialize the player

ScreenGameplayState::ScreenGameplayState(){}

ScreenGameplayState& ScreenGameplayState::getInstance()
{
	static ScreenGameplayState singleton;
	return singleton;
}

void ScreenGameplayState::InitScreen(void)
{
	framesCounter = 0;
	finishScreen = 0;

	//Background texture
	landscape = LoadTexture("resources/Game/Landscape.png");

	 //Start player
	Vector2 screenSize = { (float)GetScreenWidth(), (float)GetScreenHeight() };
	player.Init(screenSize);

	//Start enemies
	enemyManager.InitEnemies();
}

//Verify if Player win or not, and if he had been hit.
void ScreenGameplayState::UpdateScreen(float deltaTime)
{
	EvaluateInput();
	framesCounter++;

	// GAMEPLAY
	player.Update(deltaTime, landscape);
	//verify if player win or not
	GameManager& GameInst = GameManager::GetGameManager();
	if (GameInst.GetScore() >= 1640) {
		GameInst.SetGameResult(true);
		GameInst.SetScore(0);
		player.SetLives(3);
		finishScreen = 4;
	}
	if (enemyManager.CheckCollisionWithPlayer(player.GetPosition(), player.GetSize())) {
		player.DecreaseLife();
		if (player.GetLives() <= 0) {
			GameManager& GameInst = GameManager::GetGameManager();
			GameInst.SetGameResult(false);
			GameInst.SetScore(0);
			player.SetLives(3);
			finishScreen = 4; // END SCREEN
		}
	}

	// Update enemies
	enemyManager.UpdateEnemies(deltaTime);

	//Detect collisions between player bullets and enemies
	for (int i = 0; i < MAX_PROYECTILES; i++) {
		if (player.GetProyectil(i).IsLanzado()) {
			enemyManager.CheckCollisionWithProjectile(player.GetProyectil(i));			
		}
	}	
}

//Draw background, score and other elements
void ScreenGameplayState::DrawScreen(void)
{

	//Background
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
	DrawTexture(landscape, (GetScreenWidth() - (landscape.width)) / 2, (GetScreenHeight() - landscape.height) / 4, WHITE);

	//Player
	player.Draw();

	//Enemies
	enemyManager.DrawEnemies();	

	// UI Score
	GameManager& GameInst = GameManager::GetGameManager();
	Font font = GameInst.GetArcadeFont();	
	float textWidth = MeasureTextEx(GameInst.GetArcadeFont(), "Press 'O' for Instructions", 25, 3).x;
	float posx = (275) - (textWidth / 2.f);
	DrawTextEx(font, "SCORE:", Vector2{ posx, 100.f }, 25, 3, WHITE);
	DrawText(to_string(GameInst.GetScore()).c_str(), posx+130, 100.f, 25, WHITE);	
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
void ScreenGameplayState::UnloadScreen(void)
{
	UnloadTexture(landscape);
	player.Unload();
	enemyManager.UnloadEnemies();
}