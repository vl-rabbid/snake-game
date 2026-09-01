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

		game.screenHeight = LEVEL_HEIGHT * CELL_SIZE;
		game.screenWidth = LEVEL_WIDTH * CELL_SIZE;

		game.speed = INITIAL_SPEED;
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
		static float timer = 0.f;
		float interval = 1.f / game.speed;

		timer += deltaTime;
		if (timer >= interval)
		{
			UpdateSnake(game.snake);

			timer -= interval;
		}
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
