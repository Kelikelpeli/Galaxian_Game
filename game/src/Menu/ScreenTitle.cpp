#include "ScreenTitle.h"
#include "raylib.h"
#include "Game/Managers/GameManager.h"
#include <xstring>

ScreenTitleState& ScreenTitleState::getInstance()
{
	static ScreenTitleState singleton;
	return singleton;
}


void ScreenTitleState::InitScreen(void)
{
	framesCounter = 0;
	finishScreen = 0;
	TraceLog(LOG_INFO, "ScreenTitleState::InitScreen");

	// Use this to access to the Game instance
	GameManager& GameInst = GameManager::GetGameManager();
	logoGalaxian = LoadTexture("resources/Menu/MainLogo.png");
	fxStart = LoadSound("resources/Sounds/02. Start Game.mp3");
	SetSoundVolume(fxStart, 0.5f);
	PlaySound(fxStart);

	text = "by Raquel L.";
	currentCharIndex = 0;
	blinkCounter = 0;
	blinkSpeed = 0.5f;
	isBlinking = true;


}

void ScreenTitleState::UpdateScreen(float deltaTime)
{
	GameManager& GameInst = GameManager::GetGameManager();

	//Words animation

	framesCounter++;
	if (framesCounter > 60 && framesCounter % 4 == 0)
	{
		//Blink
		if (framesCounter % 2 == 0) isBlinking = !isBlinking;
		if (currentCharIndex < strlen(text)) {
			currentCharIndex++;
		}
	}

	if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
	{
		finishScreen = 2;   // GAMEPLAY
	}

	if (IsKeyPressed(KEY_O))
	{
		finishScreen = 1;   // OPTIONS
	}
}

void ScreenTitleState::DrawScreen(void)
{
	//logo
	DrawTexture(logoGalaxian, (GetScreenWidth() - (logoGalaxian.width)) / 2, (GetScreenHeight() - logoGalaxian.height) / 4, WHITE);
	GameManager& GameInst = GameManager::GetGameManager();

	float textWidth = MeasureTextEx(GameInst.GetArcadeFont(), text, 20, 2).x; // Aseguramos el espaciado de 2 para evitar problemas
	float posx = (GetScreenWidth() / 2.f) - (textWidth / 2.f);

	// Letter by letter
	for (int i = 0; i < strlen(text); i++)
	{
		char letter[2] = { text[i], '\0' };

		Font currentFont;
		if (i < currentCharIndex)
		{
			currentFont = GameInst.GetArcadeFont();
		}
		else
		{
			currentFont = GameInst.GetAlienFont();

		}
		DrawTextEx(currentFont, letter, Vector2{ posx, 450.f }, 20, 2, WHITE);

		//Next position
		posx += MeasureTextEx(currentFont, letter, 20, 2).x;
	}


	textWidth = MeasureTextEx(GameInst.GetArcadeFont(), "Press Enter for Playing", 25, 3).x;
	posx = (GetScreenWidth() / 2.f) - (textWidth / 2.f);
	DrawTextEx(GameInst.GetArcadeFont(), "Press Enter for Playing", Vector2{ posx, 500.f }, 25, 3, WHITE);

	textWidth = MeasureTextEx(GameInst.GetArcadeFont(), "Press 'O' for Instructions", 25, 3).x;
	posx = (GetScreenWidth() / 2.f) - (textWidth / 2.f);
	DrawTextEx(GameInst.GetArcadeFont(), "Press 'O' for Instructions", Vector2{ posx, 560.f }, 25, 3, WHITE);

}

void ScreenTitleState::UnloadScreen(void)
{
	GameManager& GameInst = GameManager::GetGameManager();
	UnloadTexture(logoGalaxian);
	UnloadSound(fxStart);
}

int ScreenTitleState::FinishScreen(void)
{
	return finishScreen;
}