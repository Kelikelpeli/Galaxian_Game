#pragma once
#include "raylib.h"

enum EnemyType { Empty, Enemy1, Enemy2, Enemy3, Enemy4 };

class Enemy {
public:
    void InitEnemy(float x, float y);
    void UpdateEnemy(float deltaTime);
    void DrawEnemy();
    EnemyType GetType();
    void SetType(EnemyType type);
    float GetX();        
    float GetY();
    bool IsAlive();
    void SetAlive(bool isAlive);

    void MoveEnemy(float dirX, float dirY);

    Rectangle GetRectangle();

private:
    Rectangle enemyRect;
    EnemyType type;
    bool isAlive;

   
public:

};
