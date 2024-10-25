#pragma once

#include "raylib.h"
#include "Proyectil.h"
#define COOLDOWN 0.5
class Player {
public:
    Player();
    void Init(Vector2 screenSize);
    void Update(float deltaTime, Texture2D landscape);
    void Draw();
    void Unload();
    void DecreaseLife();

    Vector2 GetPosition() const;
    int GetLives() const;
    void SetLives(int lives);
    Vector2 GetSize() const;
    Proyectil& GetProyectil(int index);

private:
    void Shoot(float deltaTime);

    Texture2D playerTexture = { 0 };;
    Vector2 position = { 0 };;
    float speed;
    int lives;
    float cooldown;
    static const int MAX_PROYECTILES = 10;
    Proyectil proyectiles[MAX_PROYECTILES];
};
