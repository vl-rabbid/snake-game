#include "Game.h"

namespace SnakeGame
{
	bool IsGameRunning(Game &game)
	{
		if (game.gameState == GameState::ExitGame)
		{
			return false;
		}
		return true;
	}

	void SetGameState(Game &game, const GameState &gameState)
	{
		game.gameState = gameState;
	}

	void InitGame(Game &game)
	{
		int seed = (int)time(nullptr);
		srand(seed);

		game.screenHeight = GRID_HEIGHT * GRID_CELL_SIZE;
		game.screenWidth = GRID_WIDTH * GRID_CELL_SIZE;

		SetGameState(game, GameState::GameLoop);
	}

	void HandleImputAndEvents(Game &game, const sf::Event &event)
	{
		if (event.type == sf::Event::Closed)
		{
			SetGameState(game, GameState::ExitGame);
			return;
		}
	}

	void UpdateGame(Game &game, const float deltaTime)
	{
	}

	void DrawGame(Game &game, sf::RenderWindow &window)
	{
	}

	void DeinitializeGame(Game &game, sf::RenderWindow &window)
	{
		window.close();
	}

}
