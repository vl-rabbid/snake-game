#pragma once
#include <string>
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	const int CELL_SIZE = 12;
	const int LEVEL_WIDTH = 20;
	const int LEVEL_HEIGHT = 13;
	const int HUD_HEIGHT = 2;
	const std::string CONFIG_FILE_NAME = "config.ini";
	const int LEADERBOARD_SIZE = 15;

	const int INPUT_BUFFER_SIZE = 2;
	const int NUM_MENU_BUTTONS = 4;

	const sf::Color COLOR_TINT(0, 0, 0, 100);
	const sf::Color COLOR_SHADOW(0, 0, 0, 150);
	const sf::Color COLOR_TEXT(54, 46, 40);
}
