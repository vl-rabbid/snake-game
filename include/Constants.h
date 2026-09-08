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

	const sf::Color COLOR_TINT(0, 0, 0, 100);
	const sf::Color COLOR_BASE(17, 41, 41);
}
