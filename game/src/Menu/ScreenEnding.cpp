#include "ScreenEnding.h"
#include "Game/Managers/GameManager.h"

#include "raylib.h"

#include <string>


ScreenEndingState& ScreenEndingState::getInstance()
{
	static ScreenEndingState singleton;
	return singleton;
}


void ScreenEndingState::InitScreen(void)
{
	framesCounter = 0;
	finishScreen = 0;

	//posiciones iniciales de las letras game over
	for (int i = 0; i < 9; i++)
	{
		letterYPositions[i] = -100;
	}

	lettersFallSpeed = 5;
	currentLetterIndex = 0;
}

void ScreenEndingState::UpdateScreen(float deltaTime)
{
	framesCounter++;

	//animacion Game Over
	if (currentLetterIndex < 9 && framesCounter % 25 == 0)
	{
		currentLetterIndex++;
		lettersFallSpeed = 5;
	}

	for (int i = 0; i < currentLetterIndex; i++)
	{
		if (letterYPositions[i] < (GetScreenHeight() / 2.f) - 150)
		{
			letterYPositions[i]  += lettersFallSpeed;
			lettersFallSpeed += 1;  //aceleracion
		}
	}

	if (IsKeyPressed(KEY_ENTER) )
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
		DrawTextEx(font, "YOU WIN!", Vector2{ (GetScreenWidth() - MeasureTextEx(font, "YOU WIN!", font.baseSize * 2.0f, 1).x) / 2.f, (GetScreenHeight() / 2.f) - 150 }, font.baseSize * 2.0f, 1, WHITE);

	}
	else
	{
		//DrawTextEx(font, "GAME OVER", Vector2{ (GetScreenWidth() - MeasureTextEx(font, "GAME OVER", font.baseSize * 2.5f, 1).x) / 2.f, (GetScreenHeight() / 2.f) - 150 }, font.baseSize * 2.5f, 1, RED);

		const char* text = "GAME OVER";
		float posX = (GetScreenWidth() - MeasureTextEx(font, text, font.baseSize * 2.5f, 1).x) / 2.0f;

		// Dibuja cada letra individualmente en su posición actual
		for (int i = 0; i < 9; i++) {
			char letter[2] = { text[i], '\0' };  // Convertir la letra a cadena
			DrawTextEx(font, letter, Vector2{ posX,float(letterYPositions[i]) }, font.baseSize * 2.5f, 1, RED);
			posX += MeasureTextEx(font, letter, font.baseSize * 2.5f, 1).x;  // Mueve la posición X para la siguiente letra
		}
	}

	DrawTextEx(font, "Press Enter for Playing", Vector2{ (GetScreenWidth() - MeasureTextEx(font, "Press Enter for Playing", 25, 2).x) / 2.f, 450.f }, 25, 2, WHITE);
	DrawTextEx(font, "Press 'O' for Options", Vector2{ (GetScreenWidth() - MeasureTextEx(font, "Press 'O' for Options", 25, 2).x) / 2.f, 500.f }, 25, 2, WHITE);


}

void ScreenEndingState::UnloadScreen(void)
{
	//Let's unload all the enemies lines
	GameManager& GameInst = GameManager::GetGameManager();


}

int  ScreenEndingState::FinishScreen(void)
{
	return finishScreen;
}