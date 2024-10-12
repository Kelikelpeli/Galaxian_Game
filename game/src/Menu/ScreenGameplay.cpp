
#pragma once

#include "ScreenGameplay.h"
#include "raylib.h"
#include "Game/Managers/GameManager.h"
#include "Game/GlobalGameDefines.h"

#include <string>




ScreenGameplayState::ScreenGameplayState()
{

}

ScreenGameplayState& ScreenGameplayState::getInstance()
{
	static ScreenGameplayState singleton;
	return singleton;
}

void ScreenGameplayState::InitScreen(void)
{
	framesCounter = 0;
	finishScreen = 0;

	//TEXTURES
	landscape = LoadTexture("resources/Game/Landscape.png");
	player = LoadTexture("resources/Game/Player.png");
	
	//player
	pjPosX = (GetScreenWidth() / 2.f);
	pjPosY = (GetScreenHeight() - 30.f - 75.f);
	pjSpeed = 120.f;
	pjWidth = player.width * 1.f;		//anchura, se comenta para rec rojo
	pjHeight = player.height * 1.f;	//altura, se comenta para rec rojo

	//proyectiles
	for (int i = 0; i < MAX_PROYECTILES; i++)
	{
		proyectil[i] = { 0, 0, 3.f, 13.f };
		pyLanzado[i] = false;
	}

	pyEnfriamiento = 0;

}

void ScreenGameplayState::UpdateScreen(float deltaTime)
{
	EvaluateInput();
	framesCounter++;
	pyEnfriamiento -= deltaTime;
	// GAMEPLAY

	//player
	if (IsKeyDown(KEY_D) && pjPosX + pjWidth < ((GetScreenWidth() - landscape.width) / 2) + landscape.width)
	{
		pjPosX += pjSpeed * deltaTime * 1.f;
		//pyPosX = pjPosX + (pjWidth / 2) - (pyWidth / 2);

	}

	if (IsKeyDown(KEY_A) && pjPosX > (GetScreenWidth() - landscape.width) / 2)
	{
		pjPosX += pjSpeed * deltaTime * -1.f;

	}
	//proyecitles
	if (IsKeyPressed(KEY_SPACE) && pyEnfriamiento <= 0)
	{
		LanzarProyectil();
		pyEnfriamiento = 0.5f; //reinicio de espera
	}

	for (int i = 0; i < MAX_PROYECTILES; i++)
	{
		if (pyLanzado[i]) {
			proyectil[i].y -= pySpeed * deltaTime; // Movimiento hacia arriba

			// Si el proyectil sale de la pantalla, se destruye
			if (proyectil[i].y + proyectil[i].height < 0) {
				pyLanzado[i] = false;
			}
		}
	}
}
void ScreenGameplayState::LanzarProyectil()
{
	for (int i = 0; i < MAX_PROYECTILES; i++) {
		if (!pyLanzado[i]) {
			proyectil[i].x = pjPosX + (pjWidth / 2) - (proyectil[i].width / 2);  // Centra el proyectil en el jugador
			proyectil[i].y = pjPosY - proyectil[i].height;  // Aparece encima del jugador
			pyLanzado[i] = true;  // Activa el proyectil
			break;  // Lanza un solo proyectil
		}
	}
}

void ScreenGameplayState::DrawScreen(void)
{

	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
	DrawTexture(landscape, (GetScreenWidth() - (landscape.width)) / 2, (GetScreenHeight() - landscape.height) / 4, WHITE);

	//Player
	DrawTexture(player, pjPosX, pjPosY, WHITE);
	//DrawRectangle(posXPj, posYPj, pjWidth, pjHeight, RED);

	//Proyectiles
	for (int i = 0; i < MAX_PROYECTILES; i++) 
	{
		if (pyLanzado[i]) {
			DrawRectangleRec(proyectil[i], YELLOW);

		}
		else if (!pyLanzado[i] && pyEnfriamiento <=0 )
		{
			proyectil[i].x = pjPosX + (pjWidth / 2) - (proyectil[i].width / 2);  // Centra el proyectil en el jugador
			proyectil[i].y = pjPosY - proyectil[i].height;
			DrawRectangleRec(proyectil[i], YELLOW);
		}
		

	}


	GameManager& GameInst = GameManager::GetGameManager();

	// UI Score, lives

	Font font = GameInst.GetArcadeFont();

	//DrawTextEX(font,"SCORE:", 300.f, 100.f, 25, WHITE);
	float textWidth = MeasureTextEx(GameInst.GetArcadeFont(), "Press 'O' for Instructions", 25, 3).x;
	float posx = (GetScreenWidth() / 2.f) - (textWidth / 2.f);
	DrawTextEx(font, "SCORE:", Vector2{ posx, 300.f }, 25, 3, WHITE);
	DrawText(to_string(GameInst.GetScore()).c_str(), 440.f, 100.f, 25, WHITE);


}

void ScreenGameplayState::InitScreen(void) {
	// Other initializations
	enemyManager.InitEnemies();  // Initialize enemies
}

void ScreenGameplayState::UpdateScreen(float deltaTime) {
	// Other updates
	enemyManager.UpdateEnemies(deltaTime);  // Update enemies
}

void ScreenGameplayState::DrawScreen(void) {
	// Other draws
	enemyManager.DrawEnemies();  // Draw enemies
}


void ScreenGameplayState::UnloadScreen(void)
{
	UnloadTexture(landscape);
	UnloadTexture(player);
}

int  ScreenGameplayState::FinishScreen(void)
{
	return finishScreen;
}

void ScreenGameplayState::EvaluateInput()
{

	if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
	{
		finishScreen = 4;   // END SCREEN
	}
}

void ScreenGameplayState::DebugOptions()
{

}

void ScreenGameplayState::DrawDebug()
{
	GameManager& GameInst = GameManager::GetGameManager();

}