#include "Game.h"
#include "Level.h"

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
		InitLevel(game.level);
		InitSnake(game.snake);
		for (int i = 0; i < game.snake.segments.size(); i++)
		{
			SetCellType(game.level, game.snake.segments[i].position, CellType::SnakeCell);
		}
		SpawnApple(game.level);
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
			SnakeSegment snakeTail = game.snake.segments.back();
			UpdateSnake(game.snake);
			SnakeSegment snakeHead = game.snake.segments.front();

			if (GetCellType(game.level, snakeHead.position) == CellType::Apple)
			{
				AddSnakeSegment(game.snake, snakeTail);
				SetCellType(game.level, snakeHead.position, CellType::SnakeCell);
				UpdateCellColor(game.level, snakeHead.position);
				SpawnApple(game.level);
			}
			else
			{
				SetCellType(game.level, snakeTail.position, CellType::Empty);
				SetCellType(game.level, snakeHead.position, CellType::SnakeCell);
			}
			timer -= interval;
		}
	}

	void DrawGame(Game &game, sf::RenderWindow &window)
	{
		DrawLevel(game.level, window);
		DrawSnake(game.snake, window);
	}

	void DeinitializeGame(Game &game, sf::RenderWindow &window)
	{
		window.close();
	}

}
