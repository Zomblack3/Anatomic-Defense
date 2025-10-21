#include "player.h"

#include "game.h"

#include <raymath.h>

namespace playerFeatures
{
	float accelerationDelay = 0.0f;

	void setPlayerDirection(Player& player)
	{
		// Calculate triangle vertices based on position, size, height, and rotation
		player.v1 = { player.position.x + sinf(player.rotation * DEG2RAD) * (player.height), player.position.y - cosf(player.rotation * DEG2RAD) * (player.height) };
		player.v2 = { player.position.x - cosf(player.rotation * DEG2RAD) * (player.size / 2), player.position.y - sinf(player.rotation * DEG2RAD) * (player.size / 2) };
		player.v3 = { player.position.x + cosf(player.rotation * DEG2RAD) * (player.size / 2), player.position.y + sinf(player.rotation * DEG2RAD) * (player.size / 2) };
	}

	void drawPlayer(Player player)
	{
		DrawTriangle(player.v1, player.v2, player.v3, player.color);
	}

	void movePlayer(Player& player, float deltaTime)
	{
		if (player.isActive)
		{
			player.speed.x = static_cast <float> (sin(player.rotation * DEG2RAD) * player.baseSpeed);
			player.speed.y = static_cast <float> (cos(player.rotation * DEG2RAD) * player.baseSpeed);

			if (accelerationDelay <= 0)
			{
				if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
				{
					player.speed.x = static_cast <float> (sin(player.rotation * DEG2RAD) * player.baseSpeed);
					player.speed.y = static_cast <float> (cos(player.rotation * DEG2RAD) * player.baseSpeed);

					accelerationDelay = 1.0f;

					if (player.lastAcceleration > 0.0f)
						player.lastAcceleration -= 0.004f;
					else if (player.lastAcceleration < 0.0f)
						player.lastAcceleration = 0.0f;
					else
						if (player.acceleration < 1)
							player.acceleration += 0.004f;
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

	void rotatePlayer(Player& player)
	{
		float mouseX = static_cast <float> (GetMouseX());
		float mouseY = static_cast <float> (GetMouseY());

		float deltaX = mouseX - player.position.x;
		float deltaY = mouseY - player.position.y;

		float angle = static_cast <float> (atan2(deltaY, deltaX));
		float grades = angle * (180.0f / PI) + 90.0f;

		player.rotation = grades;

		/*if (player.rotation > grades)
			player.rotation -= 2.0f;
		else if (player.rotation < grades)
			player.rotation += 2.0f;*/

		/*if (IsKeyDown(KEY_LEFT)) 
			player.rotation -= 5.0f * deltaTime;
		if (IsKeyDown(KEY_RIGHT)) 
			player.rotation += 5.0f * deltaTime;

		if (player.rotation >= 360.0f)
			player.rotation -= 360.0f;
		if (player.rotation < 0.0f)
			player.rotation += 360.0f;*/
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

namespace playerShooting
{
	void moveBullet(Bullet bullets[], int amountOfBullets, float deltaTime)
	{
		for (int i = 0; i < amountOfBullets; i++)
		{
			if (bullets[i].isActive)
			{
				bullets[i].position.x += bullets[i].speed.x * deltaTime;
				bullets[i].position.y -= bullets[i].speed.y * deltaTime;

				if (bullets[i].position.x > settings::screenWidth || bullets[i].position.x < 0 ||
					bullets[i].position.y > settings::screenHeight || bullets[i].position.y < 0)
					bullets[i].isActive = false;
			}
		}
	}

	void shootBullet(Player player, Bullet bullets[], int amountOfBullets)
	{
		for (int i = 0; i < amountOfBullets; i++)
		{
			if (!bullets[i].isActive)
			{
				bullets[i].isActive = true;
				// Set bullet position and speed based on player position and rotation
				bullets[i].position = player.v1;
				bullets[i].speed.x = static_cast <float>(sin(player.rotation * DEG2RAD) * bullets[i].baseSpeed);
				bullets[i].speed.y = static_cast <float>(cos(player.rotation * DEG2RAD) * bullets[i].baseSpeed);
				bullets[i].direction = player.direction;
				break; // Shoot only one bullet at a time
			}
		}
	}

	void drawBullets(Bullet bullets[], int amountOfBullets)
	{
		for (int i = 0; i < amountOfBullets; i++)
		{
			if (bullets[i].isActive)
				DrawCircleV(bullets[i].position, bullets[i].radius, bullets[i].color);
		}
	}
}
