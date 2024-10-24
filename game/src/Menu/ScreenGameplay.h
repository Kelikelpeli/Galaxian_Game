#pragma once
#include "StateMachineMngr.h"
#include "raylib.h"
#include "screen.h"
#include "../Game/Player.h"
#include "../Game/Managers/EnemyManager.h"

#define MAX_PROYECTILES 4

class ScreenGameplayState : public StateMachineMngr
{
public:

	void enter(Screen* screen) {}
	void toggle(Screen* screen) {};
	void exit(Screen* screen) {};

	virtual void InitScreen(void);
	virtual void UpdateScreen(float deltaTime);
	virtual void DrawScreen(void);
	virtual void UnloadScreen(void);
	virtual int FinishScreen(void);

	int getScreenId() { return (int)ScreenState::GAMEPLAY; }

	static ScreenGameplayState& getInstance();


private:
	ScreenGameplayState();
	ScreenGameplayState(const ScreenGameplayState& other);
	ScreenGameplayState& operator= (const ScreenGameplayState& other);

	//texturas
	Texture2D landscape = { 0 };
	
	void EvaluateInput();
	
	void DebugOptions();
	void DrawDebug();

	int framesCounter = 0;
	int finishScreen = 0;
	bool mb_ReplayLevel = false;

	bool debug_floor = false;
	bool debug_stairs = false;

	EnemyManager enemyManager;

};