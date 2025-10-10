#pragma once

#include <raylib.h>

namespace run
{
	void game();
}

namespace settings
{
	constexpr int screenWidth = 1250;
	constexpr int screenHeight = 750;

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