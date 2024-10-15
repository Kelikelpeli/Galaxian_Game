#pragma once
#include "raylib.h"
//#define MAX_PROYECTILES 4


class Proyectil {
public:
    void InitProyectil(float x, float y, float width, float height, float speed, bool active, float direccionY);
    void UpdateProyectil(float deltaTime);
    void DrawProyectil();
    void Launcher(float startX, float startY);
    bool IsActive();
    void SetActive(bool active);
    void Deactivate();
    void Reinicio();
    Rectangle GetRectangle();
    bool IsLanzado();
    void SetLanzado(bool lanzado);

private:
    Rectangle proyectilRect;
    float speed;
    bool active;
    bool lanzado;

    float direccionY;  // 1 para ir hacia arriba, -1 para ir hacia abajo

};