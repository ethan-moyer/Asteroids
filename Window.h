#pragma once
#include "Ship.h"
#include "Bullet.h"
#include <raylib.h>
#include <memory>
#include <vector>
#include "Asteroid.h"

class Window
{
public:
	static void Init();
	static void Quit();
	static void Update();
	static void SpawnBullet(Vector2 spawnPosition, float angle);
	static void SpawnAsteroid(Vector2 spawnPosition, int type, float angle);
	static std::vector<std::shared_ptr<Asteroid>> GetAsteroids();
	static bool gameOver;
	static bool gameStarted;
private:
	static void StartGame();
	static void SpawnStartingAsteroids();
	static Ship ship;
	static std::vector<Bullet> bullets;
	static std::vector<std::shared_ptr<Asteroid>> asteroids;
};

