#pragma once

#include <raylib.h>

const int maxAmountOfBullets = 100;

struct Bullet
{
	Vector2 position = { 0.0f, 0.0f };
	Vector2 speed = { 0.0f, 0.0f };
	Vector2 direction = { 0.0f, 0.0f };
	
	Color color = YELLOW;

	float radius = 5.0f;
	float baseSpeed = 5.0f;

	bool isActive = false;
};

struct Player
{
	Vector2 position = { 0.0f, 0.0f };
	Vector2 speed = { 0.0f, 0.0f };
	Vector2 direction = { 0.0f, 0.0f };

	// Triangle vertices
	Vector2 v1 = { 0.0f, 0.0f };
	Vector2 v2 = { 0.0f, 0.0f };
	Vector2 v3 = { 0.0f, 0.0f };

	Color color = RED;

	Bullet bullets[maxAmountOfBullets];

	const float baseSpeed = 6.0f;
	
	float lastAcceleration = 0.0f;
	float acceleration = 0.0f;
	float lastRotation = 0.0f; // in degrees
	float rotation = 0.0f; // in degrees

	float size = 20.0f;
	float height = 0.0f;

	int health = 100;
	int score = 0;
	
	bool isAlive() const { return health > 0; };
	bool isActive = false;
};

namespace playerFeatures
{
	void setPlayerDirection(Player& player);
	void drawPlayer(Player player);
	void movePlayer(Player& player, float deltaTime);
	void rotatePlayer(Player& player);
	void takeDamage(Player& player, int damage);
	void addScore(Player& player, int points);
	void setDefault(Player& player);
}

namespace playerShooting
{
	void moveBullet(Bullet bullets[], int amountOfBullets, float deltaTime);
	void shootBullet(Player player, Bullet bullets[], int amountOfBullets);
	void drawBullets(Bullet bullets[], int amountOfBullets);
}