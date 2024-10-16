
#pragma once

#include "ScreenGameplay.h"
#include "raylib.h"
#include "Game/Managers/GameManager.h"
#include "Game/GlobalGameDefines.h"
#include "../Game/Proyectil.h"

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

	//TEXTURAS
	landscape = LoadTexture("resources/Game/Landscape.png");
	player = LoadTexture("resources/Game/Player.png");

	//player
	pjPosX = (GetScreenWidth() / 2.f);
	pjPosY = (GetScreenHeight() - 30.f - 75.f);
	pjSpeed = 120.f;
	//pjWidth = player.width * 1.f;		//anchura, se comenta para rec rojo
	//pjHeight = player.height * 1.f;	//altura, se comenta para rec rojo

	//proyectiles de player
	for (int i = 0; i < MAX_PROYECTILES; i++)
	{
		pjProyectiles[i].InitProyectil(pjPosX + (player.width / 2) - 1.5f, pjPosY - 13.f, 3.f, 13.f, 100.f, false, 1);
		pjProyectiles[i].SetLanzado(false);
	}
	pjProyectiles[0].SetActive(true);

	pyEnfriamiento = 0;

	// Inicializar enemigos
	enemyManager.InitEnemies();

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

	}

	if (IsKeyDown(KEY_A) && pjPosX > (GetScreenWidth() - landscape.width) / 2)
	{
		pjPosX += pjSpeed * deltaTime * -1.f;

	}
	

	//proyecitles del player

		//lanzar proyectil

	if (IsKeyPressed(KEY_SPACE) && pyEnfriamiento <= 0)
	{
		LanzarProyectil(deltaTime);
		pyEnfriamiento = 0.5f; //reinicio de espera
	}

	for (int i = 0; i < MAX_PROYECTILES; i++)
	{
		pjProyectiles[i].UpdateProyectil(deltaTime);

		if (!pjProyectiles[i].IsLanzado() && pyEnfriamiento<=0)
		{
			if (i == 0) 
			{
				pjProyectiles[i].Launcher(pjPosX + (player.width / 2) - (pjProyectiles[i].GetRectangle().width / 2), pjPosY - pjProyectiles[i].GetRectangle().height);

			}
			else if (pjProyectiles[i-1].IsLanzado())
			{
				pjProyectiles[i].Launcher(pjPosX + (player.width / 2) - (pjProyectiles[i].GetRectangle().width / 2), pjPosY - pjProyectiles[i].GetRectangle().height);

			}
			pjProyectiles[i].Launcher(pjPosX + (player.width / 2) - (pjProyectiles[i].GetRectangle().width / 2), pjPosY - pjProyectiles[i].GetRectangle().height);
			break;
		}
		pjProyectiles[i].UpdateProyectil(deltaTime);

	
			//colisiones
		if (pjProyectiles[i].IsLanzado() && !enemyManager.DetectarColisiones(pjProyectiles[i].GetRectangle()))
		{
			//pjProyectiles[i].InitProyectil(0, 0, 3.f, 13.f, 250.f, false,1);
			pjProyectiles[i].Deactivate();

		}


	}
	
	for (int i = 0; i < MAX_PROYECTILES; i++)
	{
		pjProyectiles[i].UpdateProyectil(deltaTime);
	}

	// Actualizar enemigos

	enemyManager.UpdateEnemies(deltaTime);
}
void ScreenGameplayState::LanzarProyectil(float deltaTime)
{
	for (int i = 0; i < MAX_PROYECTILES; i++)
	{
		if (!pjProyectiles[i].IsLanzado())
		{
			//pjProyectiles[i].Launcher((pjProyectiles[i].GetRectangle().width / 2), pjPosY - pjProyectiles[i].GetRectangle().height);
			//pjProyectiles[i].Launcher(pjPosX + (player.width / 2) - (pjProyectiles[i].GetRectangle().width / 2), pjPosY - pjProyectiles[i].GetRectangle().height);
			pjProyectiles[i].SetLanzado(true);
			break;
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
		
		pjProyectiles[i].DrawProyectil();
	}
	//for (int i = 0; i < MAX_PROYECTILES; i++) 
	//{

	//	if (pyLanzado[i]) {
	//		DrawRectangleRec(proyectil[i], YELLOW);

	//	}
	//	else if (!pyLanzado[i] && pyEnfriamiento <=0 )
	//	{
	//		proyectil[i].x = pjPosX + (pjWidth / 2) - (proyectil[i].width / 2);  // Centra el proyectil en el jugador
	//		proyectil[i].y = pjPosY - proyectil[i].height;
	//		DrawRectangleRec(proyectil[i], YELLOW);
	//	}
	//	

	//}

	// Dibujar enemigos
	enemyManager.DrawEnemies();


	GameManager& GameInst = GameManager::GetGameManager();

	// UI Score, lives

	Font font = GameInst.GetArcadeFont();

	//DrawTextEX(font,"SCORE:", 300.f, 100.f, 25, WHITE);
	float textWidth = MeasureTextEx(GameInst.GetArcadeFont(), "Press 'O' for Instructions", 25, 3).x;
	float posx = (GetScreenWidth()-1000) - (textWidth / 2.f);
	DrawTextEx(font, "SCORE:", Vector2{ posx, 100.f }, 25, 3, WHITE);
	DrawText(to_string(GameInst.GetScore()).c_str(), 440.f, 100.f, 25, WHITE);




}
//void ScreenGameplayState::DetectarColisiones() {
//
//
//}

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