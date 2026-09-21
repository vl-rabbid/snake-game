#pragma once
#include <string>
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	const int AUDIO_TRACK_COUNT = 2;
	const int CELL_SIZE = 12;
	const int LEVEL_WIDTH = 20;
	const int LEVEL_HEIGHT = 13;
	const int HUD_HEIGHT = 2;
	const unsigned int RENDER_WIDTH = LEVEL_WIDTH * CELL_SIZE;
	const unsigned int RENDER_HEIGHT = (LEVEL_HEIGHT + HUD_HEIGHT) * CELL_SIZE;
	const std::string GAME_NAME = "Snake Game";

	const std::string CONFIG_FILE_NAME = "config.ini";
	const int LEADERBOARD_SIZE = 15;

	const int INPUT_BUFFER_SIZE = 2;
	const int MAX_MENU_BUTTONS = 4;
	const int DISPLAYED_LEVEL_COUNT = 3;
	const float SELECTOR_SPEED = 40.f;
	const float SLIDER_SPEED = 30.f;
	const float INPUT_MARKER_INTERVAL = 0.5f;
	const int LEADERBOARD_DISPLAYED = 5;

	const float DELAY_COUNTDOWN = 3.2f;
	const float DELAY_GAME_OVER = 1.5f;

	const sf::Color COLOR_TINT(0, 0, 0, 100);
	const sf::Color COLOR_SHADOW(0, 0, 0, 150);
	const sf::Color COLOR_TEXT(54, 46, 40);
	const sf::Color COLOR_INPUT_TEXT(184, 159, 128);

	const sf::Color COLOR_GREEN_LIGHT(113, 180, 55);
	const sf::Color COLOR_GREEN_DARK(79, 160, 65);
	const sf::Color COLOR_SNAKE(24, 95, 229);
	const sf::Color COLOR_WALL(82, 81, 110);
}
