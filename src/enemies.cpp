#include "enemies.h"

#include <raymath.h>

#include "settings.h"

namespace enemiesFeatures
{
	const float baseSpeedSmall = 400.0f;
	const float baseSpeedMedium = 300.0f;
	const float baseSpeedBig = 200.0f;

	const float radiusSmall = 20.0f;
	const float radiusMedium = 25.0f;
	const float radiusBig = 35.0f;

	const int pointsSmall = 10;
	const int pointsMedium = 25;
	const int pointsBig = 40;

	float spawnTimer = 0.0f;
	float baseSpawnTime = 500.0f;

	void spawnEnemy(std::vector <Enemy>& enemies, Texture smallEnemy, Texture mediumEnemy, Texture bigEnemy, float deltaTime)
	{
		Enemy enemy = { };

		int randomEnemyType = 0;
		int randomPosY = 0;

		ENEMY_TYPE enemyType = ENEMY_TYPE::SMALL;

		Vector2 enemySpeed = { };
		Vector2 enemyPos = { };

		if (spawnTimer <= 0 && enemies.size() < 100)
		{
			enemy.rotation = static_cast <float> (GetRandomValue(0, 360));

			randomEnemyType = GetRandomValue(1, 3);

			enemyPos.x = static_cast <float>(GetRandomValue(0, screenWidth));

			if (enemyPos.x > 5 || enemyPos.x < screenWidth - 5)
			{
				randomPosY = GetRandomValue(0, 100);

				if (randomPosY < 50)
					enemyPos.y = 0;
				else
					enemyPos.y = screenHeight;
			}
			else
				enemyPos.y = static_cast <float> (GetRandomValue(0, screenHeight));

			switch (randomEnemyType)
			{
			case 1:

				enemyType = ENEMY_TYPE::SMALL;
				enemy.radius = radiusSmall;
				enemy.baseSpeed = baseSpeedSmall;
				enemy.points = pointsSmall;
				enemy.texture = smallEnemy;

				break;
			case 2:

				enemyType = ENEMY_TYPE::MEDIUM;
				enemy.radius = radiusMedium;
				enemy.baseSpeed = baseSpeedMedium;
				enemy.points = pointsMedium;
				enemy.texture = mediumEnemy;

				break;
			case 3:

				enemyType = ENEMY_TYPE::BIG;
				enemy.radius = radiusBig;
				enemy.baseSpeed = baseSpeedBig;
				enemy.points = pointsBig;
				enemy.texture = bigEnemy;

				break;
			default:
				break;
			}

			enemy.speed.x = static_cast <float> (sin(enemy.rotation * DEG2RAD) * enemy.baseSpeed);
			enemy.speed.y = static_cast <float> (cos(enemy.rotation * DEG2RAD) * enemy.baseSpeed);

			enemy.type = enemyType;
			enemy.position = enemyPos;
			enemy.speed = enemySpeed;

			enemies.push_back(enemy);

			spawnTimer = baseSpawnTime;

			baseSpawnTime -= deltaTime * 100;
		}
		else
			spawnTimer -= deltaTime * 100;
	}

	void splitEnemy(std::vector<Enemy>& enemies, Enemy enemySplited, ENEMY_TYPE type, int index, Texture smallEnemy, Texture mediumEnemy)
	{
		Enemy enemy1 = setSplitedEnemy(type, enemySplited.position, smallEnemy, mediumEnemy);
		Enemy enemy2 = setSplitedEnemy(type, enemySplited.position, smallEnemy, mediumEnemy);

		enemies.erase(enemies.begin() + index);

		enemies.push_back(enemy1);
		enemies.push_back(enemy2);
	}

	void moveEnemy(std::vector <Enemy>& enemies, float deltaTime)
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies.at(i).position.x += enemies.at(i).speed.x = static_cast <float>(sin(enemies.at(i).rotation * DEG2RAD) * enemies.at(i).baseSpeed) * deltaTime;
			enemies.at(i).position.y -= enemies.at(i).speed.y = static_cast <float>(cos(enemies.at(i).rotation * DEG2RAD) * enemies.at(i).baseSpeed) * deltaTime;

			if (enemies.at(i).position.x > screenWidth + enemies.at(i).radius)
				enemies.at(i).position.x = -(enemies.at(i).radius);
			else if (enemies.at(i).position.x < -(enemies.at(i).radius))
				enemies.at(i).position.x = screenWidth + enemies.at(i).radius;

			if (enemies.at(i).position.y > (screenHeight + enemies.at(i).radius))
				enemies.at(i).position.y = -(enemies.at(i).radius);
			else if (enemies.at(i).position.y < -(enemies.at(i).radius))
				enemies.at(i).position.y = screenHeight + enemies.at(i).radius;
		}
	}

	void drawEnemy(std::vector <Enemy> enemies)
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			switch (enemies.at(i).type)
			{
			case ENEMY_TYPE::SMALL:

				DrawTexture(enemies.at(i).texture, static_cast <int>(enemies.at(i).position.x - enemies.at(i).radius), static_cast <int>(enemies.at(i).position.y - enemies.at(i).radius), WHITE);

				break;
			case ENEMY_TYPE::MEDIUM:

				DrawTexture(enemies.at(i).texture, static_cast <int>(enemies.at(i).position.x - enemies.at(i).radius), static_cast <int>(enemies.at(i).position.y - enemies.at(i).radius), WHITE);

				break;
			case ENEMY_TYPE::BIG:
				
				DrawTexture(enemies.at(i).texture, static_cast <int>(enemies.at(i).position.x - enemies.at(i).radius - enemies.at(i).radius / 2) - 10, static_cast <int>(enemies.at(i).position.y - enemies.at(i).radius - enemies.at(i).radius / 2), WHITE);
				
				break;
			default:
				break;
			}

			/*if (enemies.at(i).type != ENEMY_TYPE::SMALL && enemies.at(i).type != ENEMY_TYPE::BIG)
				DrawCircle(static_cast <int>(enemies.at(i).position.x), static_cast <int>(enemies.at(i).position.y), enemies.at(i).radius, enemies.at(i).color);*/
		}
	}

	void checkBulletEnemyCollition(std::vector<Enemy>& enemies, Player& player, Texture smallEnemy, Texture mediumEnemy, Texture bigEnemy)
	{
		float distanceX = 0.0f;
		float distanceY = 0.0f;
		float totalDistance = 0.0f;

		for (int i = 0; i < enemies.size(); i++)
		{
			for (int j = 0; j < maxAmountOfBullets; j++)
			{
				if (player.bullets[j].isActive && enemies.size() != 0)
				{
					if (player.bullets[j].position.x > enemies.at(i).position.x)
						distanceX = player.bullets[j].position.x - enemies.at(i).position.x;
					else
						distanceX = enemies.at(i).position.x - player.bullets[j].position.x;

					if (player.bullets[j].position.y > enemies.at(i).position.y)
						distanceY = player.bullets[j].position.y - enemies.at(i).position.y;
					else
						distanceY = enemies.at(i).position.y - player.bullets[j].position.y;

					totalDistance = static_cast <float> (sqrt((distanceX * distanceX) + (distanceY * distanceY)));

					if (totalDistance <= enemies.at(i).radius + player.bullets[j].radius)
					{
						playerFeatures::addScore(player, enemies.at(i).points);

						if (enemies.at(i).type != ENEMY_TYPE::SMALL)
							splitEnemy(enemies, enemies.at(i), enemies.at(i).type, i, smallEnemy, mediumEnemy);
						else
							enemies.erase(enemies.begin() + i);

						player.bullets[j].isActive = false;

						if (i != 0)
							i--;
					}
				}
			}
		}
	}

	void checkPlayerEnemyCollition(std::vector<Enemy>& enemies, Player& player, float deltaTime, Texture smallEnemy, Texture mediumEnemy, Texture bigEnemy)
	{
		float distanceX = 0.0f;
		float distanceY = 0.0f;
		float totalDistance = 0.0f;

		if (player.untouchableTimer <= 0)
		{
			for (int i = 0; i < enemies.size(); i++)
			{
				if (player.pos.x > enemies.at(i).position.x)
					distanceX = player.pos.x - enemies.at(i).position.x;
				else
					distanceX = enemies.at(i).position.x - player.pos.x;

				if (player.pos.y > enemies.at(i).position.y)
					distanceY = player.pos.y - enemies.at(i).position.y;
				else
					distanceY = enemies.at(i).position.y - player.pos.y;

				totalDistance = static_cast <float> (sqrt((distanceX * distanceX) + (distanceY * distanceY)));

				if (totalDistance <= enemies.at(i).radius + player.hitboxRadius)
				{
					player.lives--;

					if (enemies.at(i).type != ENEMY_TYPE::SMALL)
						splitEnemy(enemies, enemies.at(i), enemies.at(i).type, i, smallEnemy, mediumEnemy);
					else
						enemies.erase(enemies.begin() + i);

					player.untouchableTimer = 50.0f;
				}
			}
		}
		else
			player.untouchableTimer -= deltaTime * 100;
	}

	Enemy setSplitedEnemy(ENEMY_TYPE type, Vector2 position, Texture smallEnemy, Texture mediumEnemy)
	{
		Enemy enemy;

		enemy.isActive = true;

		enemy.rotation = static_cast <float> (GetRandomValue(0, 360));

		switch (type)
		{
		case ENEMY_TYPE::MEDIUM:

			enemy.type = ENEMY_TYPE::SMALL;
			enemy.radius = radiusSmall;
			enemy.baseSpeed = baseSpeedSmall;
			enemy.points = pointsSmall;
			enemy.texture = smallEnemy;

			break;
		case ENEMY_TYPE::BIG:
			
			enemy.type = ENEMY_TYPE::MEDIUM;
			enemy.radius = radiusMedium;
			enemy.baseSpeed = baseSpeedMedium;
			enemy.points = pointsMedium;
			enemy.texture = mediumEnemy;

			break;
		default:

			break;
		}

		enemy.speed.x = static_cast <float> (sin(enemy.rotation * DEG2RAD) * enemy.baseSpeed);
		enemy.speed.y = static_cast <float> (cos(enemy.rotation * DEG2RAD) * enemy.baseSpeed);

		enemy.position = position;

		return enemy;
	}
}
