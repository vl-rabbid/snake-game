#pragma once
#include <string>
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	const int CELL_SIZE = 12;
	const int LEVEL_WIDTH = 20;
	const int LEVEL_HEIGHT = 13;
	const int UI_HEIGHT = 2;
	const float SCREEN_SCALE = 4.f;

	const float INITIAL_SPEED = 8.f; // Snake moves cells per second
	const int INITIAL_SEGMENT_NUMBER = 3;
	const int INPUT_BUFFER_SIZE = 2;
	const int NUM_MENU_BUTTONS = 3;

	const sf::Color COLOR_GRASS_LIGHT(169, 215, 82);
	const sf::Color COLOR_GRASS_DARK(163, 208, 75);
	const sf::Color COLOR_SNAKE(70, 112, 229);
	const sf::Color COLOR_APPLE(230, 74, 32);
	const sf::Color COLOR_WALL(75, 117, 40);
}
