#include "Ship.h"
#include <raymath.h>
#include "Window.h"
#include <iostream>
#include "ResourceManager.h"

const float Ship::SIZE = 20;
const float Ship::START_ANGLE = 90;
const float Ship::TURN_RATE = 270;
const float Ship::ACCELERATION = 800;
const float Ship::FRICTION = 3;
const float Ship::MAX_SPEED = 600;
const std::string Ship::TEX_PATH = "Resources/Ship.png";
const std::string Ship::SHIP_SOUND_PATH = "Resources/Ship.ogg";
const std::string Ship::SHOOT_SOUND_PATH = "Resources/Shoot.ogg";
const std::string Ship::CRASH_SOUND_PATH = "Resources/Crash.ogg";

Ship::Ship()
{
	position = Vector2Zero();
	velocity = Vector2Zero();
	angle = 0;
	texture = { 0, 0, 0, 0, 0 };
	shipSound = { {NULL, NULL, 0, 0, 0}, 0 };
	shootSound = { {NULL, NULL, 0, 0, 0}, 0 };
	crashSound = { {NULL, NULL, 0, 0, 0}, 0 };
}

Ship::Ship(Vector2 startPosition)
{
	position = startPosition;
	velocity = Vector2Zero();
	angle = START_ANGLE;
	texture = ResourceManager::GetTexture(TEX_PATH);
	shipSound = ResourceManager::GetSound(SHIP_SOUND_PATH);
	shootSound = ResourceManager::GetSound(SHOOT_SOUND_PATH);
	crashSound = ResourceManager::GetSound(CRASH_SOUND_PATH);
}

void Ship::Update()
{
	// Rotate ship
	if (IsKeyDown(KEY_LEFT))
	{
		angle += TURN_RATE * GetFrameTime();
	}
	if (IsKeyDown(KEY_RIGHT))
	{
		angle -= TURN_RATE * GetFrameTime();
	}

	// Accelerate in forward direction
	Vector2 forward = { cosf(DEG2RAD * angle), -sinf(DEG2RAD * angle) };
	if (IsKeyDown(KEY_UP))
	{
		velocity = Vector2Add(velocity, Vector2Scale(forward, ACCELERATION * GetFrameTime()));
		velocity = Vector2ClampValue(velocity, 0, MAX_SPEED);

		if (!IsSoundPlaying(shipSound))
			PlaySound(shipSound);
	}
	else if (Vector2Length(velocity) > 0.05)
	{
		velocity = Vector2Subtract(velocity, Vector2Scale(velocity, FRICTION * GetFrameTime()));
	}

	// Update position
	position = Vector2Add(position, Vector2Scale(velocity, GetFrameTime()));

	// Horizontal looping
	if (position.x > GetScreenWidth() + SIZE)
	{
		position.x = -SIZE;
	}
	else if (position.x < -SIZE)
	{
		position.x = GetScreenWidth() + SIZE;
	}

	// Vertical looping
	if (position.y > GetScreenHeight() + SIZE)
	{
		position.y = -SIZE;
	}
	else if (position.y < -SIZE)
	{
		position.y = GetScreenHeight() + SIZE;
	}

	// Shoot bullets
	if (IsKeyPressed(KEY_SPACE))
	{
		PlaySound(shootSound);
		Window::SpawnBullet(Vector2Add(position, Vector2Scale(forward, 2 * SIZE)), angle);
	}

	// Asteroid collision check
	for (int i = 0; i < Window::GetAsteroids().size(); ++i)
	{
		if (CheckCollisionCircles(position, SIZE, Window::GetAsteroids()[i]->GetPosition(), Window::GetAsteroids()[i]->GetSize()))
		{
			PlaySound(crashSound);
			Window::gameOver = true;
			break;
		}
	}
}

void Ship::Draw()
{
	Rectangle srcRect = { 0, 0, (float)texture.width, (float)texture.height };
	Rectangle destRect = { position.x, position.y, (float)texture.width, (float)texture.height };
	Vector2 origin = { (float)texture.width / 2, (float)texture.height / 2 };
	DrawTexturePro(texture, srcRect, destRect, origin, -angle + 90, WHITE);

	#ifdef _DEBUG
		DrawCircle(position.x, position.y, 16, { 255, 0, 0, 125 });

		std::string printVel = std::to_string(Vector2Length(velocity));
		DrawText(printVel.c_str(), 10, 30, 12, DARKGREEN);
	#endif
}
