#pragma once
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Level.h"
#include "GameState.h"

namespace SnakeGame
{
	struct Game
	{
		int screenWidth;
		int screenHeight;
		GameState gameState;
		Level level;
		Snake snake;
		float speed;
	};

	bool IsGameRunning(Game &game);

	void SetGameState(Game &game, const GameState &gameState);

	void InitGame(Game &game);

	void HandleImputAndEvents(Game &game, const sf::Event &event);

	void UpdateGame(Game &game, const float deltaTime);

	void DrawGame(Game &game, sf::RenderWindow &window);

	void DeinitializeGame(Game &game, sf::RenderWindow &window);
}
