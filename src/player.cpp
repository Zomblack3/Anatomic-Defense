#include "player.h"

#include <raymath.h>

namespace playerFeatures
{
	void setPlayerDirection(Player& player)
	{
		int frameWidth = player.texture.width;
		int frameHeight = player.texture.height;

		player.textureRec.x = 0.0f;
		player.textureRec.y = 0.0f;
		player.textureRec.width = static_cast <float> (frameWidth);
		player.textureRec.height = static_cast <float> (frameHeight);

		player.textureDest.x = player.pos.x - (player.texture.width / 2.0f);
		player.textureDest.y = player.pos.y - (player.texture.height / 2.0f);
		player.textureDest.width = player.textureRec.width;
		player.textureDest.height = player.textureRec.height;

		player.textureOrigin.x = player.texture.width / 2.0f;
		player.textureOrigin.y = player.texture.height / 2.0f;

		player.texturePos.x = player.textureOrigin.x - player.texture.width;
		player.texturePos.y = player.textureOrigin.y - player.texture.height;

		player.hitboxPos.x = player.textureDest.x;
		player.hitboxPos.y = player.textureDest.y;
	}

	void drawPlayer(const Player player)
	{
		DrawTexturePro(player.texture, player.textureRec, player.textureDest, player.textureOrigin, player.rotation, WHITE);
	}

	void movePlayer(Player& player, const float deltaTime)
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			player.speed.x += static_cast <float> (sin(player.rotation * DEG2RAD) * player.acceleration);
			player.speed.y += static_cast <float> (cos(player.rotation * DEG2RAD) * player.acceleration);

			if (player.acceleration < player.maxAcceleration)
				player.acceleration += baseAcceleration;
			else
				player.acceleration = player.maxAcceleration;
		}
		else
		{
			if (player.acceleration > player.minAcceleration)
				player.acceleration -= baseAcceleration;
			else
				player.acceleration = player.minAcceleration;
		}

		if (IsKeyDown(KEY_DOWN))
		{
			if (player.acceleration > 0)
				player.acceleration -= baseAcceleration;
			else if (player.acceleration < 0)
				player.acceleration = 0;
		}

		player.pos.x += (player.speed.x * deltaTime);
		player.pos.y -= (player.speed.y * deltaTime);

		if (player.pos.x > screenWidth + player.height)
			player.pos.x = -(player.height);
		else if (player.pos.x < -(player.height))
			player.pos.x = screenWidth + player.height;

		if (player.pos.y > (screenHeight + player.height))
			player.pos.y = -(player.height);
		else if (player.pos.y < -(player.height))
			player.pos.y = screenHeight + player.height;
	}

	void rotatePlayer(Player& player)
	{
		float mouseX = static_cast <float> (GetMouseX());
		float mouseY = static_cast <float> (GetMouseY());

		float deltaX = mouseX - player.pos.x;
		float deltaY = mouseY - player.pos.y;

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

	void addScore(Player& player, int points)
	{
		player.score += points;
	}

	void setDefault(Player& player)
	{
		player.pos = { 0.0f, 0.0f };
		player.speed = { 0.0f, 0.0f };
		player.color = RED;
		player.acceleration = 0.0f;
		player.rotation = 0.0f;
		player.lives = 3;
		player.score = 0;
	}

	bool isAlive(const Player player)
	{
		return player.lives > 0;
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

				if (bullets[i].position.x > screenWidth || bullets[i].position.x < 0 ||
					bullets[i].position.y > screenHeight || bullets[i].position.y < 0)
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
				bullets[i].position.x = player.hitboxPos.x;
				bullets[i].position.y = player.hitboxPos.y;
				bullets[i].speed.x = static_cast <float>(sin(player.rotation * DEG2RAD) * bullets[i].baseSpeed);
				bullets[i].speed.y = static_cast <float>(cos(player.rotation * DEG2RAD) * bullets[i].baseSpeed);

				InitAudioDevice();

				PlaySound(player.shotSound);

				CloseAudioDevice();

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
