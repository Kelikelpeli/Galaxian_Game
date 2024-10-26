#include "ScreenEnding.h"
#include "Game/Managers/GameManager.h"

#include "raylib.h"

#include <string>

ScreenEndingState& ScreenEndingState::getInstance()
{
	static ScreenEndingState singleton;
	return singleton;
}
ScreenEndingState::ScreenEndingState() {}

void ScreenEndingState::InitScreen(void)
{

	framesCounter = 0;
	finishScreen = 0;

	//start position letters game over
	for (int i = 0; i < 9; i++)
	{
		letterYPositions[i] = -100;
	}
	lettersFallSpeed = 5;
	currentLetterIndex = 0;

	winScale = 0.0f;
	scaleSpeed = 0.2f;
	scalingUp = true;
}

void ScreenEndingState::UpdateScreen(float deltaTime)
{
	framesCounter++;
	GameManager& GameInst = GameManager::GetGameManager();

	//Game Over start
	if (!GameInst.GetGameResult())
	{

		if (currentLetterIndex < 9 && framesCounter % 25 == 0)
		{
			currentLetterIndex++;
			lettersFallSpeed = 5;
		}

		for (int i = 0; i < currentLetterIndex; i++)
		{
			if (letterYPositions[i] < (GetScreenHeight() / 2.f) - 150)
			{
				letterYPositions[i] += lettersFallSpeed;
				lettersFallSpeed += 1;  //Aceleration
			}
		}
	}
	//Win start
	else
	{
		if (scalingUp)
		{
			winScale += scaleSpeed;
			if (winScale >= 3.5f) scalingUp = false;
		}
		else
		{
			winScale -= scaleSpeed;
			if (winScale <= 2.5f) scalingUp = true;

			//stop the animation
			if (scaleSpeed > 0.01f) {
				scaleSpeed *= 0.93f;
			}
			else {
				winScale = 3.0f;
			}
		}
	}

	//To go to another screens...
	if (IsKeyPressed(KEY_ENTER))
	{
		finishScreen = 1; // GAMEPLAY

	}
	if (IsKeyPressed(KEY_O))
	{
		finishScreen = 2;   // OPTIONS
	}
}

void ScreenEndingState::DrawScreen(void)
{
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
	GameManager& GameInst = GameManager::GetGameManager();

	Font font = GameInst.GetArcadeFont();

	// Write this in case of win
	if (GameInst.GetGameResult())
	{
		Vector2 textSize = MeasureTextEx(font, "YOU WIN!", font.baseSize * winScale, 1);
		DrawTextEx(font, "YOU WIN!", Vector2{ (GetScreenWidth() - textSize.x) / 2.f, (GetScreenHeight() / 2.f) - 150 },
			font.baseSize * winScale, 1, YELLOW);
	}
	else
	{
		const char* text = "GAME OVER";
		float posX = (GetScreenWidth() - MeasureTextEx(font, text, font.baseSize * 2.5f, 1).x) / 2.0f;

		for (int i = 0; i < 9; i++) {
			char letter[2] = { text[i], '\0' };
			DrawTextEx(font, letter, Vector2{ posX,float(letterYPositions[i]) }, font.baseSize * 2.5f, 1, RED);
			posX += MeasureTextEx(font, letter, font.baseSize * 2.5f, 1).x;
		}
	}

	DrawTextEx(font, "Press Enter for Playing", Vector2{ (GetScreenWidth() - MeasureTextEx(font, "Press Enter for Playing", 25, 2).x) / 2.f, 450.f }, 25, 2, WHITE);
	DrawTextEx(font, "Press 'O' for Options", Vector2{ (GetScreenWidth() - MeasureTextEx(font, "Press 'O' for Options", 25, 2).x) / 2.f, 500.f }, 25, 2, WHITE);
}
void ScreenEndingState::UnloadScreen(void)
{
}

int  ScreenEndingState::FinishScreen(void)
{
	return finishScreen;
}