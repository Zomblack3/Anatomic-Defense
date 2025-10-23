#pragma once

#include <raylib.h>

namespace run
{
	void game();
}

namespace settings
{
	constexpr int screenWidth = 1024;
	constexpr int screenHeight = 768;

	enum class Screen
	{
		MAIN_MENU,
		GAMEPLAY,
		WIN_SCREEN,
		LOSE_SCREEN,
		OPTIONS,
		EXIT
	};
}