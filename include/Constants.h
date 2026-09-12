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
	const int MAX_MENU_BUTTONS = 4;
	const int DISPLAYED_LEVEL_COUNT = 3;

	const sf::Color COLOR_TINT(0, 0, 0, 100);
	const sf::Color COLOR_SHADOW(0, 0, 0, 150);
	const sf::Color COLOR_TEXT(54, 46, 40);

	const sf::Color COLOR_GREEN_LIGHT(113, 180, 55);
	const sf::Color COLOR_GREEN_DARK(79, 160, 65);
	const sf::Color COLOR_SNAKE(24, 95, 229);
	const sf::Color COLOR_WALL(82, 81, 110);
}
