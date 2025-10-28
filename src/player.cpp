#include "player.h"

#include <iostream>
#include <raymath.h>

namespace playerFeatures
{
	void setPlayerDirection(Player& player)
	{
		int frameWidth = player.texture.width;
		int frameHeight = player.texture.height;

		// Calculate triangle vertices based on position, size, height, and rotation
		player.v1 = { player.pos.x + sinf(player.rotation * DEG2RAD) * (player.height), player.pos.y - cosf(player.rotation * DEG2RAD) * (player.height) };
		player.v2 = { player.pos.x - cosf(player.rotation * DEG2RAD) * (player.size / 2), player.pos.y - sinf(player.rotation * DEG2RAD) * (player.size / 2) };
		player.v3 = { player.pos.x + cosf(player.rotation * DEG2RAD) * (player.size / 2), player.pos.y + sinf(player.rotation * DEG2RAD) * (player.size / 2) };

		/*player.hitboxPos.x = (player.v1.x + player.v2.x + player.v3.x) / 3.0;
		player.hitboxPos.y = (player.v1.y + player.v2.y + player.v3.y) / 3.0;*/

		/*player.texturePos.x = player.hitboxPos.x;
		player.texturePos.y = player.hitboxPos.y;*/

		//player.textureRec.x = player.hitboxPos.x - (player.hitboxRadius / 2.0f);
		//player.textureRec.y = player.hitboxPos.y - (player.hitboxRadius / 2.0f);
		//player.textureRec.width = player.texture.width / 2.0f;
		//player.textureRec.height = player.texture.height / 2.0f;

		player.textureRec.x = 0.0f;
		player.textureRec.y = 0.0f;
		player.textureRec.width = static_cast <float> (frameWidth);
		player.textureRec.height = static_cast <float> (frameHeight);

		player.textureDest.x = player.pos.x - (player.texture.width / 2.0f);
		player.textureDest.y = player.pos.y - (player.texture.height / 2.0f);
		player.textureDest.width = player.textureRec.width;
		player.textureDest.height = player.textureRec.height;

		player.textureOrigin.x = player.pos.x;
		player.textureOrigin.y = player.pos.y;

		player.texturePos.x = player.textureOrigin.x - player.texture.width;
		player.texturePos.y = player.textureOrigin.y - player.texture.height;

		player.hitboxPos.x = player.textureOrigin.x + (player.texture.width / 2.0f);
		player.hitboxPos.y = player.textureOrigin.y + (player.texture.height / 2.0f);

		//player.textureRecDestination.x = /*player.hitboxPos.x + (player.hitboxRadius / 2.0f)*/ player.hitboxPos.x;
		//player.textureRecDestination.y = /*player.hitboxPos.y + (player.hitboxRadius / 2.0f)*/ player.hitboxPos.y;
		//player.textureRecDestination.width = player.texture.width;
		//player.textureRecDestination.height = player.texture.height;
	}

	void drawPlayer(const Player player)
	{
		Rectangle testRec = { screenWidth / 2.0f, screenHeight / 2.0f, player.texture.width * 2.0f, player.texture.height * 2.0f };
		Vector2 testVector = { screenWidth / 2.0f, screenHeight / 2.0f };

		DrawTriangle(player.v1, player.v2, player.v3, player.color);
		
		//DrawTextureEx(player.texture, player.textureOrigin, player.rotation, 1, WHITE);
		//DrawRectangleLines(player.textureOrigin.x, player.textureOrigin.y, player.texture.width, player.texture.height, RED);
		//DrawTexture(player.texture, hitboxPosX - (player.texture.width / 2.0f), hitboxPosY - (player.texture.height / 2.0f), WHITE);
		//DrawTexturePro(player.texture, player.textureRec, player.textureRecDestination, player.textureOrigin, player.rotation, WHITE);
		//DrawTexturePro(player.texture, player.textureRec, player.textureDest, player.textureOrigin, 0, WHITE);
		
		//DrawTexturePro(player.texture, player.textureRec, testRec, testVector, 0.0f, WHITE);

		//DrawTexture(player.texture, screenWidth / 2.0f, screenHeight / 2.0f, WHITE);

		std::cout << "Textura X: " << player.textureOrigin.x << std::endl;
		std::cout << "Textura Y: " << player.textureOrigin.y << std::endl;
		
		DrawCircle(static_cast <int> (player.hitboxPos.x), static_cast <int> (player.hitboxPos.y), player.hitboxRadius, BLUE);
	}

	void movePlayer(Player& player, const float deltaTime)
	{
		if (player.isActive)
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
		else
		{
			if (IsKeyPressed(KEY_ENTER))
				player.isActive = true;
		}
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
				bullets[i].position.x = player.pos.x + (player.texture.width / 2.0f);
				bullets[i].position.y = player.pos.y;
				bullets[i].speed.x = static_cast <float>(sin(player.rotation * DEG2RAD) * bullets[i].baseSpeed);
				bullets[i].speed.y = static_cast <float>(cos(player.rotation * DEG2RAD) * bullets[i].baseSpeed);
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
