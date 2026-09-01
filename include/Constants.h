#pragma once
#include <string>
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	const int CELL_SIZE = 32;
	const int LEVEL_WIDTH = 21;
	const int LEVEL_HEIGHT = 31;
	const float INITIAL_SPEED = 8.f; // Snake moves cells per second
	const int INITIAL_SEGMENT_NUMBER = 10;
	const int INPUT_BUFFER_SIZE = 2;
}
