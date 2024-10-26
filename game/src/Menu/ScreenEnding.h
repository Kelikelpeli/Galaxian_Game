#pragma once
#include "StateMachineMngr.h"

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

	//animacion game over
	int letterYPositions[9];
	int currentLetterIndex = 0;
	int lettersFallSpeed = 0;

	//Animacion you win 
	float winScale = 0.0f;
	float scaleSpeed = 0.05f;
	bool scalingUp = true;

};