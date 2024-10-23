#include "Player.h"

Player::Player() : speed(120.f), lives(3), cooldown(0) {}

void Player::Init(Vector2 screenSize) {
    playerTexture = LoadTexture("resources/Game/Player.png");
    position = { screenSize.x / 2.f, screenSize.y - 105.f }; // Near bottom-center
    for (int i = 0; i < MAX_PROYECTILES; i++) {
        proyectiles[i].InitProyectil(position.x + (playerTexture.width / 2) - 1.5f, position.y - 13.f, 3.f, 13.f, 100.f, false, 1);
        proyectiles[i].SetLanzado(false);
    }
    proyectiles[0].SetActive(true);
}

void Player::Update(float deltaTime, Texture2D landscape) {
    if (IsKeyDown(KEY_D)) position.x += speed * deltaTime;
    if (IsKeyDown(KEY_A)) position.x -= speed * deltaTime;

    //limitar movimiento
    if (position.x < (GetScreenWidth() - landscape.width) / 2.0f)
    {
        position.x = (GetScreenWidth() - landscape.width) / 2.0f;
    }
    if (position.x + playerTexture.width > (GetScreenWidth() - landscape.width) / 2.0f + landscape.width)
    {
        position.x = (GetScreenWidth() - landscape.width) / 2.0f + landscape.width - playerTexture.width;
    }
    cooldown -= deltaTime;
    if (IsKeyPressed(KEY_SPACE) && cooldown <= 0) {
        Shoot(deltaTime);
        cooldown = 0.5f;
    }

    for (int i = 0; i < MAX_PROYECTILES; i++) {
        proyectiles[i].UpdateProyectil(deltaTime);
    }
}

void Player::Draw() const {
    DrawTexture(playerTexture, position.x, position.y, WHITE);
    for (int i = 0; i < MAX_PROYECTILES; i++) {
        proyectiles[i].DrawProyectil();
    }

    //representación de vidas
    for (int i = 0; i < lives; i++) {
        DrawTextureEx(playerTexture, Vector2{ 75.f + (i * 40), (float)GetScreenHeight() - 70 }, 0.0f, 0.7f, ORANGE);
    }
   /* for (int i = 0; i < lives; i) {
        DrawTexture(playerTexture, (GetScreenWidth()-1030) - (i + 1) * 50, GetScreenHeight() - 100, ORANGE);
    }*/
}

void Player::Shoot(float deltaTime) {
    for (int i = 0; i < MAX_PROYECTILES; i++) {
        if (!proyectiles[i].IsLanzado()) {
            proyectiles[i].SetLanzado(true);
            break;
        }
    }
}

void Player::Unload() {
    UnloadTexture(playerTexture);
}

Vector2 Player::GetPosition() const {
    return position;
}

int Player::GetLives() const {
    return lives;
}

void Player::DecreaseLife() {
    if (lives > 0) {
        lives--;
    }
}
Vector2 Player::GetSize() const {
    return Vector2{ (float)playerTexture.width, (float)playerTexture.height };
}
Proyectil& Player::GetProyectil(int index) {
    return proyectiles[index];
}


