
#pragma once
#include "StateMachineMngr.h"
#include "Screen.h"
#include "raylib.h"

class ScreenTitleState : public StateMachineMngr
{
public:

	void enter(Screen* screen){}
	void toggle(Screen* screen){};
	void exit(Screen* screen){};

	void InitScreen(void);
	void UpdateScreen(float deltaTime);
	void DrawScreen(void);
	void UnloadScreen(void);
	int FinishScreen(void);

	int getScreenId() { return (int)ScreenState::TITLE; }

	static ScreenTitleState& getInstance();

private:

	ScreenTitleState(){};
	ScreenTitleState(const ScreenTitleState& other);
	ScreenTitleState& operator= (const ScreenTitleState& other);

	int framesCounter = 0;
	int finishScreen = 0;

	Texture2D logoGalaxian = { 0 };
	Sound fxStart = { 0 };

	//Draw by Raquel L.
	int currentCharIndex = 0;
	int blinkCounter = 0;
	int blinkSpeed = 0;
	bool isBlinking = true;

	const char* text;

	
};