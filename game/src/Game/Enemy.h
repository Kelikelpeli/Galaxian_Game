#pragma once
#include "raylib.h"
#define MAX_PROYECTILES 4


enum EnemyType { Empty, Enemy1, Enemy2, Enemy3, Enemy4 };

class Enemy {
public:
    void InitEnemy(float x, float y);
    void DrawEnemy();
    EnemyType GetType()const;
    void SetType(EnemyType type);
    float GetX()const;
    float GetY()const;
    bool IsAlive()const;
    void SetAlive(bool isAlive);
    void MoveEnemy(float dirX, float dirY);
    Rectangle GetRectangle() const;

private:
    Rectangle enemyRect;
    EnemyType type;
    bool isAlive;   
};
