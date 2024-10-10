
#pragma once

#include "ScreenGameplay.h"
#include "raylib.h"
#include "Game/Managers/GameManager.h"
#include "Game/GlobalGameDefines.h"

#include <string>


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

	landscape = LoadTexture("resources/Game/Landscape.png");
	player = LoadTexture("resources/Game/Player.png");
	enemy1 = LoadTexture("resources/Game/Enemy1.png");
	enemy2 = LoadTexture("resources/Game/Enemy2.png");
	enemy3 = LoadTexture("resources/Game/Enemy3.png");
	enemy4 = LoadTexture("resources/Game/Enemy4.png");

	//player
	posXPj = (GetScreenWidth() / 2);
	posYPj = (GetScreenHeight() - 30 - 75);
	startPos = { posXPj, posYPj };
	pjSpeed = 120;

}

void ScreenGameplayState::UpdateScreen(float deltaTime)
{
	EvaluateInput();
	framesCounter++;
	// GAMEPLAY

	if (IsKeyDown(KEY_D) && posXPj + pjWidth < ((GetScreenWidth() - landscape.width) / 2) + landscape.width)
	{
		posXPj += pjSpeed * deltaTime * 1.f;


	}


	if (IsKeyDown(KEY_A) && posXPj >(GetScreenWidth() - landscape.width) / 2)
	{
		posXPj += pjSpeed * deltaTime * -1.f;
	}
	pj = { posXPj,posYPj, pjWidth, pjHeight };


}

void ScreenGameplayState::DrawScreen(void)
{

	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
	DrawTexture(landscape, (GetScreenWidth() - (landscape.width)) / 2, (GetScreenHeight() - landscape.height) / 4, WHITE);
	DrawRectangle(posXPj, posYPj, pjWidth, pjHeight, RED);


	GameManager& GameInst = GameManager::GetGameManager();

	// UI Score, lives

	Font font = GameInst.GetArcadeFont();

	//DrawTextEX(font,"SCORE:", 300.f, 100.f, 25, WHITE);
	float textWidth = MeasureTextEx(GameInst.GetArcadeFont(), "Press 'O' for Instructions", 25, 3).x;
	float posx = (GetScreenWidth() / 2.f) - (textWidth / 2.f);
	DrawTextEx(font, "SCORE:", Vector2{ posx, 300.f }, 25, 3, WHITE);
	DrawText(to_string(GameInst.GetScore()).c_str(), 440.f, 100.f, 25, WHITE);


}

void ScreenGameplayState::UnloadScreen(void)
{
	UnloadTexture(landscape);
	UnloadTexture(player);
	UnloadTexture(enemy1);
	UnloadTexture(enemy2);
	UnloadTexture(enemy3);
	UnloadTexture(enemy4);
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