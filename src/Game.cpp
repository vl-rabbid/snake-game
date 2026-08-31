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

		game.screenHeight = GRID_HEIGHT * CELL_SIZE;
		game.screenWidth = GRID_WIDTH * CELL_SIZE;

		InitSnake(game.snake, game);

		SetGameState(game, GameState::GameLoop);
	}

	void HandleImputAndEvents(Game &game, const sf::Event &event)
	{
		if (event.type == sf::Event::Closed)
		{
			SetGameState(game, GameState::ExitGame);
			return;
		}
		HandleSnakeImput(game.snake, event);
	}

	void UpdateGame(Game &game, const float deltaTime)
	{
		UpdateSnake(game.snake, deltaTime);
	}

	void DrawGame(Game &game, sf::RenderWindow &window)
	{
		DrawSnake(game.snake, window);
	}

	void DeinitializeGame(Game &game, sf::RenderWindow &window)
	{
		window.close();
	}

}
