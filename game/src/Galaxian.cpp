/*******************************************************************************************
*
*   raylib game template
*
*   <Glaxian Game. PEC 1>
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2021 Ramon Santamaria (@raysan5)
*
* Created by Raquel L�pez Barcel�
********************************************************************************************/
#pragma once

#include "raylib.h"
#include "Game/GlobalGameDefines.h"
#include "Game/Managers/GameManager.h"

extern const int screenWidth = 1280;
extern const int screenHeight = 800;

extern const int gravity = 400;

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //---------------------------------------------------------
    InitWindow(GameGlobalVar::screenWidth, GameGlobalVar::screenHeight, "GALXY GAME PAC 1");

    GameManager & GameMngr = GameManager::GetGameManager();
    GameMngr.InitGame();
    
        SetTargetFPS(60);       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        float deltaTime = GetFrameTime();

        //Update Frame
        GameMngr.UpdateFrame(deltaTime);
        
        //Draw Frame
        GameMngr.GetGameManager().DrawFrame();
    }

    // De-Initialization
    GameManager::GetGameManager().UnloadGame();

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}