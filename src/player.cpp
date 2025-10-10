#include "player.h"

#include "game.h"

#include <math.h>

namespace playerFeatures
{
	float accelerationDelay = 0.0f;

	void drawPlayer(Player player)
	{
		// Calculate triangle vertices based on position, size, height, and rotation
		player.v1 = { player.position.x + sinf(player.rotation * DEG2RAD) * (player.height), player.position.y - cosf(player.rotation * DEG2RAD) * (player.height) };
		player.v2 = { player.position.x - cosf(player.rotation * DEG2RAD) * (player.size / 2), player.position.y - sinf(player.rotation * DEG2RAD) * (player.size / 2) };
		player.v3 = { player.position.x + cosf(player.rotation * DEG2RAD) * (player.size / 2), player.position.y + sinf(player.rotation * DEG2RAD) * (player.size / 2) };
		
		DrawTriangle(player.v1, player.v2, player.v3, player.color);
	}

	void move(Player& player, float deltaTime)
	{
		if (player.isActive)
		{
			player.speed.x = sin(player.rotation * DEG2RAD) * player.baseSpeed;
			player.speed.y = cos(player.rotation * DEG2RAD) * player.baseSpeed;

			if (accelerationDelay <= 0)
			{
				if (IsKeyDown(KEY_UP))
				{
					if (player.acceleration < 1)
						player.acceleration += 0.004f;

					accelerationDelay = 1.0f;
				}
				else
				{
					if (player.acceleration > 0.2f)
						player.acceleration -= 0.004f;
					else if (player.acceleration < 0.2f)
						player.acceleration = 0.2f;

					accelerationDelay = 1.0f;
				}
			}
			else
				accelerationDelay -= deltaTime;

			if (IsKeyDown(KEY_DOWN))
			{
				if (player.acceleration > 0)
					player.acceleration -= 0.04f;
				else if (player.acceleration < 0)
					player.acceleration = 0;
			}

			player.position.x += (player.speed.x * player.acceleration * deltaTime);
			player.position.y -= (player.speed.y * player.acceleration * deltaTime);

			if (player.position.x > settings::screenWidth + player.height) 
				player.position.x = -(player.height);
			else if (player.position.x < -(player.height)) 
				player.position.x = settings::screenWidth + player.height;
			
			if (player.position.y > (settings::screenHeight + player.height)) 
				player.position.y = -(player.height);
			else if (player.position.y < -(player.height)) 
				player.position.y = settings::screenHeight + player.height;
		}
		else
		{
			if (IsKeyPressed(KEY_SPACE))
				player.isActive = true;
		}
	}

	void rotate(Player& player, float deltaTime)
	{
		if (IsKeyDown(KEY_LEFT)) 
			player.rotation -= 5.0f * deltaTime;
		if (IsKeyDown(KEY_RIGHT)) 
			player.rotation += 5.0f * deltaTime;

		if (player.rotation >= 360.0f)
			player.rotation -= 360.0f;
		if (player.rotation < 0.0f)
			player.rotation += 360.0f;
	}

	void takeDamage(Player& player, int damage)
	{
		player.health -= damage;

		if (player.health < 0)
			player.health = 0;
	}

	void addScore(Player& player, int points)
	{
		player.score += points;
	}

	void setDefault(Player& player)
	{
		player.position = { 0.0f, 0.0f };
		player.speed = { 0.0f, 0.0f };
		player.color = RED;
		player.acceleration = 0.0f;
		player.rotation = 0.0f;
		player.health = 100;
		player.score = 0;
	}
}
