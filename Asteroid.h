#pragma once
#include <raylib.h>
#include <array>
#include <string>

class Asteroid
{
public:
	Asteroid();
	Asteroid(Vector2 startPosition, int type, float angle);
	void Update();
	void Draw();
	void Quit();
	void OnHit();
	Vector2 GetPosition();
	float GetSize();
	bool GetShouldBeDestroyed();
	void SetShouldBeDestroyed(bool value);
private:
	static const std::array<float, 3> SIZES;
	static const std::array<float, 3> SPEEDS;
	static const std::array<std::string, 3> TEX_PATHS;
	static const std::string SOUND_PATH;
	Vector2 position;
	Vector2 velocity;
	int type;
	bool shouldBeDestroyed;
	float spriteAngle;
	Texture2D texture;
	Sound destroySound;
};

