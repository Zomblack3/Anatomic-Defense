#include "enemies.h"

#include <raymath.h>

#include "game.h"

namespace enemiesFeatures
{
	const float baseSpeedSmall = 4.0f;
	const float baseSpeedMedium = 3.0f;
	const float baseSpeedBig = 2.5f;

	const float radiusSmall = 15.0f;
	const float radiusMedium = 25.0f;
	const float radiusBig = 35.0f;

	const int damageSmall = 15;
	const int damageMedium = 25;
	const int damageBig = 35;

	const int pointsSmall = 10;
	const int pointsMedium = 25;
	const int pointsBig = 40;

	float spawnTimer = 0.0f;
	float baseSpawnTime = 500.0f;

	void spawnEnemy(std::vector <Enemy>& enemies, float deltaTime)
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

			enemyPos.x = static_cast <float>(GetRandomValue(0, settings::screenWidth));

			if (enemyPos.x > 5 || enemyPos.x < settings::screenWidth - 5)
			{
				randomPosY = static_cast <float> (GetRandomValue(0, 100));

				if (randomPosY < 50)
					enemyPos.y = 0;
				else
					enemyPos.y = settings::screenHeight;
			}
			else
				enemyPos.y = static_cast <float> (GetRandomValue(0, settings::screenHeight));

			switch (randomEnemyType)
			{
			case 1:

				enemyType = ENEMY_TYPE::SMALL;
				enemy.radius = radiusSmall;
				enemy.baseSpeed = baseSpeedSmall;
				enemy.damage = damageSmall;
				enemy.points = pointsSmall;

				break;
			case 2:

				enemyType = ENEMY_TYPE::MEDIUM;
				enemy.radius = radiusMedium;
				enemy.baseSpeed = baseSpeedMedium;
				enemy.damage = damageMedium;
				enemy.points = pointsMedium;

				break;
			case 3:

				enemyType = ENEMY_TYPE::BIG;
				enemy.radius = radiusBig;
				enemy.baseSpeed = baseSpeedBig;
				enemy.damage = damageBig;
				enemy.points = pointsBig;

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

			baseSpawnTime -= deltaTime;
		}
		else
			spawnTimer -= deltaTime;
	}

	void splitEnemy(std::vector<Enemy>& enemies, Enemy enemySplited, ENEMY_TYPE type, int index)
	{
		Enemy enemy1 = setSplitedEnemy(type, enemySplited.speed, enemySplited.position);
		Enemy enemy2 = setSplitedEnemy(type, enemySplited.speed, enemySplited.position);

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

			if (enemies.at(i).position.x > settings::screenWidth + enemies.at(i).radius)
				enemies.at(i).position.x = -(enemies.at(i).radius);
			else if (enemies.at(i).position.x < -(enemies.at(i).radius))
				enemies.at(i).position.x = settings::screenWidth + enemies.at(i).radius;

			if (enemies.at(i).position.y > (settings::screenHeight + enemies.at(i).radius))
				enemies.at(i).position.y = -(enemies.at(i).radius);
			else if (enemies.at(i).position.y < -(enemies.at(i).radius))
				enemies.at(i).position.y = settings::screenHeight + enemies.at(i).radius;
		}
	}

	void drawEnemy(std::vector <Enemy> enemies)
	{
		for (int i = 0; i < enemies.size(); i++)
			DrawCircle(static_cast <int>(enemies.at(i).position.x), static_cast <int>(enemies.at(i).position.y), enemies.at(i).radius, enemies.at(i).color);
	}

	void checkBulletEnemyCollition(std::vector<Enemy>& enemies, Player& player)
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
							splitEnemy(enemies, enemies.at(i), enemies.at(i).type, i);
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

	void checkPlayerEnemyCollition(std::vector<Enemy>& enemies, Player& player, float deltaTime)
	{
		float distanceX = 0.0f;
		float distanceY = 0.0f;
		float totalDistance = 0.0f;

		if (player.untouchableTimer <= 0)
		{
			for (int i = 0; i < enemies.size(); i++)
			{
				if (player.position.x > enemies.at(i).position.x)
					distanceX = player.position.x - enemies.at(i).position.x;
				else
					distanceX = enemies.at(i).position.x - player.position.x;

				if (player.position.y > enemies.at(i).position.y)
					distanceY = player.position.y - enemies.at(i).position.y;
				else
					distanceY = enemies.at(i).position.y - player.position.y;

				totalDistance = static_cast <float> (sqrt((distanceX * distanceX) + (distanceY * distanceY)));

				if (totalDistance <= enemies.at(i).radius + player.hitboxRadius)
				{
					playerFeatures::takeDamage(player, enemies.at(i).damage);

					if (enemies.at(i).type != ENEMY_TYPE::SMALL)
						splitEnemy(enemies, enemies.at(i), enemies.at(i).type, i);
					else
						enemies.erase(enemies.begin() + i);

					player.untouchableTimer = 50.0f;
				}
			}
		}
		else
			player.untouchableTimer -= deltaTime;
	}

	Enemy setSplitedEnemy(ENEMY_TYPE type, Vector2 speed, Vector2 position)
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
			enemy.damage = damageSmall;
			enemy.points = pointsSmall;

			break;
		case ENEMY_TYPE::BIG:
			
			enemy.type = ENEMY_TYPE::MEDIUM;
			enemy.radius = radiusMedium;
			enemy.baseSpeed = baseSpeedMedium;
			enemy.damage = damageMedium;
			enemy.points = pointsMedium;

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
