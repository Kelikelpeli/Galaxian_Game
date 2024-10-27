#pragma once
#include "StateMachineMngr.h"
#include "raylib.h"

class ScreenEndingState : public StateMachineMngr
{
public:

	void enter(Screen* screen) {}
	void toggle(Screen* screen) {};
	void exit(Screen* screen) {};

	virtual void InitScreen(void);
	virtual void UpdateScreen(float deltaTime);
	virtual void DrawScreen(void);
	void ScreenEndingState::UnloadScreen(void);
	virtual int FinishScreen(void);

	int getScreenId() { return (int)ScreenState::ENDING; }
	
	static ScreenEndingState& getInstance();

private:
	ScreenEndingState();
	ScreenEndingState(const ScreenEndingState& other);
	ScreenEndingState& operator= (const ScreenEndingState& other);

	int framesCounter = 0;
	int finishScreen = 0;

	//GAME OVER
	int letterYPositions[9] = { 0 };
	int currentLetterIndex = 0;
	int lettersFallSpeed = 0;
	Sound fxGameOver = { 0 };

	//WIN
	float winScale = 0.0f;
	float scaleSpeed = 0.05f;
	bool scalingUp = true;
	Sound fxWin = { 0 };

};