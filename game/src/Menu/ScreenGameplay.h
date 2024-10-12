#pragma once
#include "StateMachineMngr.h"
#include "raylib.h"
#include "screen.h"
#include "EnemyManager.h"
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

	void InitEnemies();
	void UpdateEnemies(float deltaTime);
	void DrawEnemies();

private:
	ScreenGameplayState();
	ScreenGameplayState(const ScreenGameplayState& other);
	ScreenGameplayState& operator= (const ScreenGameplayState& other);

	//texturas
	Texture2D landscape = { 0 };
	Texture2D player = { 0 };
	void EvaluateInput();
	
	void DebugOptions();
	void DrawDebug();

	int framesCounter = 0;
	int finishScreen = 0;
	bool mb_ReplayLevel = false;

	bool debug_floor = false;
	bool debug_stairs = false;

	//player
	float pjPosY= 0.f;
	float pjPosX = 0.f;
	float pjSpeed = 0.f;
	float pjWidth = 25.f;
	float pjHeight = 30.f;

	//proyectiles
	
	float pySpeed = 250.f;
	float pyEnfriamiento = 0.f;  //contador para esperar 0.5 segundos entre proyectiles
	bool pyLanzado[MAX_PROYECTILES];
	Rectangle proyectil[MAX_PROYECTILES];

	void LanzarProyectil();

	EnemyManager enemyManager;

};