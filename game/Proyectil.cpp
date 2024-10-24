#include "Proyectil.h"

void Proyectil::InitProyectil(float x, float y, float width, float height, float speed, bool active, float direccionY) {
	proyectilRect = { x, y, width, height };
	this->speed = speed;
	this->active = active;
	this->direccionY = direccionY;
	lanzado = false;
}
void Proyectil::UpdateProyectil(float deltaTime) {
	if ( lanzado) {
		proyectilRect.y -= speed * direccionY * deltaTime; // Move upwards

		// Deactivate projectile if it goes out of bounds
		if (proyectilRect.y + proyectilRect.height < 0 || proyectilRect.y > GetScreenHeight()) {
			active = false;
			lanzado = false;
		}
	}
}
void Proyectil::DrawProyectil() const {
	if (active) {
		DrawRectangleRec(proyectilRect, YELLOW);
	}
}

void Proyectil::Launcher(float startX, float startY) {

	proyectilRect.x = startX - (proyectilRect.width / 2);
	proyectilRect.y = startY;
	active = true;
}

bool Proyectil::IsActive() {
	return active;
}

void Proyectil::SetActive(bool active)
{
	this->active = active;
}
bool Proyectil::IsLanzado() {
	return lanzado;
}
void Proyectil::SetLanzado(bool lanzado)
{
	this->lanzado = lanzado;
}

void Proyectil::Deactivate() {
	active = false;
	lanzado = false;
}
void Proyectil::Reinicio() {
	active = true;
	lanzado = false;
}
Rectangle Proyectil::GetRectangle() {
	return proyectilRect;
}
void Proyectil::SetPosition(float posX, float posY){
	proyectilRect.x = posX;
	proyectilRect.y = posY;
}