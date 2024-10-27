#include "ScreenLogo.h"
#include "raylib.h"

ScreenLogoState::ScreenLogoState() :chargeTime_(0) {}

ScreenLogoState& ScreenLogoState::getInstance()
{
	static ScreenLogoState singleton;
	return singleton;
}

//-------------------------------------------------------------
void ScreenLogoState::InitScreen(void)
{
	framesCounter = 0;
	lettersCount = 0;

	alpha = 0.0f;
	logo = LoadTexture("resources/Menu/Galaxia_Logo.png");
	TraceLog(LOG_DEBUG, "Loading logo texture\n");
}

//-------------------------------------------------------------
void ScreenLogoState::UpdateScreen(float deltaTime)
{
	//Start the logo drawing
	framesCounter++;
	if (framesCounter > 80)
	{
		if (alpha < 1.0) {
			alpha += 0.01f;
		}
	}
	if (framesCounter >= 240) finishScreen = 1;
}

//-------------------------------------------------------------
void ScreenLogoState::DrawScreen(void)
{
	DrawTexture(logo, (GetScreenWidth() - (logo.width)) / 2, (GetScreenHeight() - logo.height) / 2, Fade(WHITE, alpha));
}

//-------------------------------------------------------------
void ScreenLogoState::UnloadScreen(void)
{
	UnloadTexture(logo);
}

//-------------------------------------------------------------
int  ScreenLogoState::FinishScreen(void)
{
	return finishScreen;
}