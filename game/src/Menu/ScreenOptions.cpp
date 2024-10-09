#include "ScreenOptions.h"
#include "raylib.h"
#include "Game/Managers/GameManager.h"



ScreenOptionsState::ScreenOptionsState()
{

}

ScreenOptionsState& ScreenOptionsState::getInstance()
{
	static ScreenOptionsState singleton;
	return singleton;
}

void ScreenOptionsState::InitScreen(void)
{
    GameManager& GameInst = GameManager::GetGameManager();
	framesCounter = 0;
	finishScreen = 0;
}

void ScreenOptionsState::UpdateScreen(float deltaTime)
{
    GameManager& GameInst = GameManager::GetGameManager();
	if (IsKeyPressed(KEY_O))
	{
		finishScreen = 1;   // TITLE
	}
}

void ScreenOptionsState::DrawScreen(void)
{
    GameManager& GameInst = GameManager::GetGameManager();
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

    const char* line1 = "To move the spaceship use the direction keys or A,D.";
    const char* line2 = "You have 3 lives, every enemy destroyed increases your score.";
    const char* line3 = "Yellow enemies add 60 points, red 50, purple 40, and blue 30.";
    const char* line4 = "To win, you must destroy all enemies.";
    const char* line5 = "You lose if you get hit by enemy projectiles 3 times.";

    

    DrawText(line1, (GetScreenWidth() / 2) - (MeasureText(line1, 20) / 2.), 150, 20, WHITE);
    DrawText(line2, (GetScreenWidth() / 2) - (MeasureText(line2, 20) / 2.), 180, 20, WHITE);
    DrawText(line3, (GetScreenWidth() / 2) - (MeasureText(line3, 20) / 2.), 210, 20, WHITE);
    DrawText(line4, (GetScreenWidth() / 2) - (MeasureText(line4, 20) / 2.), 240, 20, WHITE);
    DrawText(line5, (GetScreenWidth() / 2) - (MeasureText(line5, 20) / 2.), 270, 20, WHITE);

    const char* line7 = "Press 'O' to return to Title.";

    float textWidth = MeasureTextEx(GameInst.GetArcadeFont(), "Press 'O' for Instructions", 25, 3).x;
    float posx = (GetScreenWidth() / 2.f) - (textWidth / 2.f);
    DrawTextEx(GameInst.GetArcadeFont(), line7, Vector2{ posx, 560.f }, 25, 3, WHITE);

}

void ScreenOptionsState::UnloadScreen(void)
{

}

int ScreenOptionsState::FinishScreen(void)
{
	return finishScreen;
}