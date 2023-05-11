#pragma once
#include <raylib.h>
#include <string>

class Ship
{
public:
	Ship();
	Ship(Vector2 startPosition);
	void Update();
	void Draw();
private:
	static const float SIZE;
	static const float START_ANGLE;
	static const float TURN_RATE;
	static const float ACCELERATION;
	static const float FRICTION;
	static const float MAX_SPEED;
	static const std::string TEX_PATH;
	static const std::string SHIP_SOUND_PATH;
	static const std::string SHOOT_SOUND_PATH;
	static const std::string CRASH_SOUND_PATH;
	Vector2 position;
	Vector2 velocity;
	float angle;
	Texture2D texture;
	Sound shipSound;
	Sound shootSound;
	Sound crashSound;
};

