#include "Asteroid.h"
#include <raymath.h>
#include "Window.h"
#include "ResourceManager.h"

const std::array<float, 3> Asteroid::SIZES = { 15, 30, 50 };
const std::array<float, 3> Asteroid::SPEEDS = { 225, 175, 100 };
const std::array<std::string, 3> Asteroid::TEX_PATHS = { "Resources/AsteroidSmall.png", "Resources/AsteroidMedium.png", "Resources/AsteroidLarge.png" };
const std::string Asteroid::SOUND_PATH = "Resources/Destroy.ogg";

Asteroid::Asteroid()
{
	position = Vector2Zero();
	velocity = Vector2Zero();
	type = 0;
	shouldBeDestroyed = false;
	spriteAngle = 0;
	texture = { 0, 0, 0, 0, 0 };
	destroySound = { {NULL, NULL, 0, 0, 0}, 0 };
}

Asteroid::Asteroid(Vector2 startPosition, int _type, float angle)
{
	position = startPosition;

	velocity = { cosf(DEG2RAD * angle), -sinf(DEG2RAD * angle) };
	velocity = Vector2Scale(velocity, SPEEDS[_type]);

	type = _type;
	shouldBeDestroyed = false;
	spriteAngle = (float)GetRandomValue(0, 359);
	texture = ResourceManager::GetTexture(TEX_PATHS[type]);
	destroySound = ResourceManager::GetSound(SOUND_PATH);
}

void Asteroid::Update()
{
	// Update position
	position = Vector2Add(position, Vector2Scale(velocity, GetFrameTime()));

	// Horizontal looping
	if (position.x > GetScreenWidth() + SIZES[type])
	{
		position.x = -SIZES[type];
	}
	else if (position.x < -SIZES[type])
	{
		position.x = GetScreenWidth() + SIZES[type];
	}

	// Vertical looping
	if (position.y > GetScreenHeight() + SIZES[type])
	{
		position.y = -SIZES[type];
	}
	else if (position.y < -SIZES[type])
	{
		position.y = GetScreenHeight() + SIZES[type];
	}
}

void Asteroid::Draw()
{
	Rectangle srcRect = { 0, 0, (float)texture.width, (float)texture.height};
	Rectangle destRect = { position.x, position.y, (float)texture.width, (float)texture.height };
	Vector2 origin = { (float)texture.width / 2, (float)texture.height / 2 };
	DrawTexturePro(texture, srcRect, destRect, origin, spriteAngle, WHITE);
	
	#ifdef _DEBUG
		DrawCircle((int)position.x, (int)position.y, SIZES[type], { 0, 0, 255, 125 });
	#endif
}

void Asteroid::Quit()
{
}

void Asteroid::OnHit()
{
	shouldBeDestroyed = true;
	PlaySound(destroySound);

	if (type > 0)
	{
		int angle = GetRandomValue(0, 359);
		Window::SpawnAsteroid(position, type - 1, (float)angle);
		Window::SpawnAsteroid(position, type - 1, (float)((angle + 180) % 360));
	}
}

Vector2 Asteroid::GetPosition()
{
	return position;
}

float Asteroid::GetSize()
{
	return SIZES[type];
}

bool Asteroid::GetShouldBeDestroyed()
{
	return shouldBeDestroyed;
}

void Asteroid::SetShouldBeDestroyed(bool value)
{
	shouldBeDestroyed = value;
}
