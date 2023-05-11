#pragma once
#include <raylib.h>

class Bullet
{
public:
	Bullet();
	Bullet(Vector2 startPosition, float angle);
	void Update();
	void Draw();
	bool GetShouldBeDestroyed();
private:
	static const float SIZE;
	static const float SPEED;
	static const float LIFETIME;
	Vector2 position;
	Vector2 velocity;
	float time;
	bool shouldBeDestroyed;
};

