#include "Bullet.h"
#include "Asteroid.h"
#include "Window.h"
#include <raymath.h>
#include <iostream>

const float Bullet::SIZE = 5;
const float Bullet::SPEED = 500;
const float Bullet::LIFETIME = 2;

Bullet::Bullet() : Bullet({ 0, 0 }, 0)
{
}

Bullet::Bullet(Vector2 startPosition, float angle)
{
	position = startPosition;
	velocity = { SPEED * cosf(DEG2RAD * angle), -SPEED * sinf(DEG2RAD * angle) };
	time = 0;
	shouldBeDestroyed = false;
}

void Bullet::Update()
{
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

    // Track bullet lifetime
    time += GetFrameTime();
    if (time >= LIFETIME)
    {
        shouldBeDestroyed = true;
    }

    // Asteroid collision
    for (int i = 0; i < Window::GetAsteroids().size(); ++i)
    {
        if (Window::GetAsteroids()[i]->GetShouldBeDestroyed())
            continue;

        if (CheckCollisionCircles(position, SIZE, Window::GetAsteroids()[i]->GetPosition(), Window::GetAsteroids()[i]->GetSize()))
        {
            std::cout << "Bullet hit asteroid!\n";
            shouldBeDestroyed = true;
            Window::GetAsteroids()[i]->OnHit();
            break;
        }
    }
}

void Bullet::Draw()
{
    DrawCircle(position.x, position.y, SIZE, WHITE);
}

bool Bullet::GetShouldBeDestroyed()
{
    return shouldBeDestroyed;
}
