#pragma once

#include <raylib.h>

struct Player
{
	Vector2 position = { 0.0f, 0.0f };
	Vector2 speed = { 0.0f, 0.0f };

	// For triangle vertices
	Vector2 v1 = { 0.0f, 0.0f };
	Vector2 v2 = { 0.0f, 0.0f };
	Vector2 v3 = { 0.0f, 0.0f };

	Color color = RED;

	const float baseSpeed = 6.0f;
	
	float acceleration = 0.0f;
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
	void drawPlayer(Player player);
	void move(Player& player, float deltaTime);
	void rotate(Player& player, float deltaTime);
	void takeDamage(Player& player, int damage);
	void addScore(Player& player, int points);
	void setDefault(Player& player);
}