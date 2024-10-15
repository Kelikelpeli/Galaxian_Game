#pragma once
#include "raylib.h"
#define MAX_PROYECTILES 4


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

   
    float pySpeed = 250.f;
    float pyEnfriamiento = 0.f;  //contador para esperar 0.5 segundos entre proyectiles
    bool pyLanzado[MAX_PROYECTILES];
    Rectangle proyectil[MAX_PROYECTILES];
};
