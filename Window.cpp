#include "Window.h"
#include "ResourceManager.h"
#include <algorithm>
#include <raylib.h>
#include <raymath.h>

Ship Window::ship;
std::vector<Bullet> Window::bullets;
std::vector<std::shared_ptr<Asteroid>> Window::asteroids;
bool Window::gameOver;
bool Window::gameStarted;

void Window::Init()
{
	InitWindow(1280, 720, "Asteroids Game");
	InitAudioDevice();
	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
	gameStarted = false;
	StartGame();
}

void Window::StartGame()
{
	Vector2 shipPos = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
	ship = Ship(shipPos);
	
	bullets.clear();

	asteroids.clear();
	SpawnStartingAsteroids();

	gameOver = false;
}

void Window::Quit()
{
	ResourceManager::Unload();
	CloseAudioDevice();
	CloseWindow();
}

void Window::Update()
{
	while (!WindowShouldClose())
	{
		// Logic
		if (!gameStarted)
		{
			if (IsKeyPressed(KEY_SPACE))
			{
				gameStarted = true;
			}
		}
		else
		{
			if (!gameOver)
			{
				ship.Update();

				std::vector<Bullet> activeBullets;
				for (int i = 0; i < bullets.size(); ++i)
				{
					bullets[i].Update();
					if (!bullets[i].GetShouldBeDestroyed())
					{
						activeBullets.push_back(bullets[i]);
					}
				}
				bullets = activeBullets;

				std::vector<std::shared_ptr<Asteroid>> activeAsteroids;
				for (int i = 0; i < asteroids.size(); ++i)
				{
					asteroids[i]->Update();
					if (!asteroids[i]->GetShouldBeDestroyed())
					{
						activeAsteroids.push_back(asteroids[i]);
					}
				}
				asteroids = activeAsteroids;
				if (asteroids.size() == 0)
				{
					gameOver = true;
				}
			}
			else
			{
				if (IsKeyPressed(KEY_SPACE))
					StartGame();
			}
		}
		
		// Rendering
		BeginDrawing();
		ClearBackground(BLACK);

		if (!gameStarted)
		{
			const char* startText = "ASTEROIDS";
			const char* subText = "ARROWS TO MOVE SPACE TO SHOOT\n       PRESS SPACE TO START";
			DrawText(startText, GetScreenWidth() / 2 - MeasureText(startText, 80) / 2, GetScreenHeight() / 2 - 40, 80, WHITE);
			DrawText(subText, GetScreenWidth() / 2 - MeasureText(subText, 30) / 2, GetScreenHeight() / 2 + 100 - 15, 30, WHITE);
		}
		else
		{
			if (!gameOver)
			{
				ship.Draw();
			}

			for (int i = 0; i < bullets.size(); ++i)
			{
				bullets[i].Draw();
			}

			for (int i = 0; i < asteroids.size(); ++i)
			{
				asteroids[i]->Draw();
			}

			if (gameOver)
			{
				if (asteroids.size() != 0)
				{
					const char* loseText = "GAME OVER";
					DrawText(loseText, GetScreenWidth() / 2 - MeasureText(loseText, 80) / 2, GetScreenHeight() / 2 - 40, 80, WHITE);
				}
				else
				{
					const char* winText = "YOU WIN";
					DrawText(winText, GetScreenWidth() / 2 - MeasureText(winText, 80) / 2, GetScreenHeight() / 2 - 40, 80, WHITE);
				}

				const char* replayText = "PRESS SPACE TO PLAY AGAIN";
				DrawText(replayText, GetScreenWidth() / 2 - MeasureText(replayText, 30) / 2, GetScreenHeight() / 2 + 100 - 15, 30, WHITE);
			}
		}

		#ifdef _DEBUG
				DrawFPS(10, 10);
		#endif

		EndDrawing();
	}
}

void Window::SpawnBullet(Vector2 spawnPosition, float angle)
{
	bullets.push_back(Bullet(spawnPosition, angle));
}

void Window::SpawnAsteroid(Vector2 spawnPosition, int type, float angle)
{
	asteroids.push_back(std::make_shared<Asteroid>(spawnPosition, type, angle));
}

std::vector<std::shared_ptr<Asteroid>> Window::GetAsteroids()
{
	return asteroids;
}

void Window::SpawnStartingAsteroids()
{
	for (int i = 0; i < 6; ++i)
	{
		bool validSpawn = false;
		while (!validSpawn)
		{
			Vector2 spawnPosition = { (float)GetRandomValue(0, GetScreenWidth()), (float)GetRandomValue(0, GetScreenHeight()) };
			if (Vector2Distance({ (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 }, spawnPosition) > 100)
			{
				SpawnAsteroid(spawnPosition, 2, (float)GetRandomValue(0, 359));
				validSpawn = true;
			}
		}
	}
}