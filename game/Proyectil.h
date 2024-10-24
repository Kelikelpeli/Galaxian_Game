#pragma once
#include "raylib.h"


class Proyectil {
public:
    void InitProyectil(float x, float y, float width, float height, float speed, bool active, float direccionY);
    void UpdateProyectil(float deltaTime);
    void DrawProyectil() const;
    void Launcher(float startX, float startY);
    bool IsActive();
    void SetActive(bool active);
    void Deactivate();
    void Reinicio();
    Rectangle GetRectangle();
    bool IsLanzado();
    void SetLanzado(bool lanzado);
    void SetPosition(float posX, float posY);

private:
    Rectangle proyectilRect;
    float speed;
    bool active;
    bool lanzado;

    float direccionY;  // 1 para ir hacia arriba, -1 para ir hacia abajo

};