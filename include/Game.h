#pragma once
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include "Snake.h"

namespace SnakeGame
{
	enum class GameState
	{
		MainMenu = 0,
		GameLoop,
		ExitGame
	};

	struct Game
	{
		int screenWidth;
		int screenHeight;
		GameState gameState;

		Snake snake;
	};

	bool IsGameRunning(Game &game);

	void SetGameState(Game &game, const GameState &gameState);

	void InitGame(Game &game);

	void HandleImputAndEvents(Game &game, const sf::Event &event);

	void UpdateGame(Game &game, const float deltaTime);

	void DrawGame(Game &game, sf::RenderWindow &window);

	void DeinitializeGame(Game &game, sf::RenderWindow &window);
}
