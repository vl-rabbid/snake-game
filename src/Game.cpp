#include "Game.h"
#include "Level.h"

namespace SnakeGame
{
	bool IsGameRunning(Game &game)
	{
		if (game.gameState == GameState::Exit)
		{
			return false;
		}
		return true;
	}

	void InitGame(Game &game)
	{
		int seed = (int)time(nullptr);
		srand(seed);

		InitResources(game.resources);

		game.gameHeight = (LEVEL_HEIGHT + UI_HEIGHT) * CELL_SIZE;
		game.gameWidth = LEVEL_WIDTH * CELL_SIZE;
		game.screenScale = SCREEN_SCALE;

		InitMenues(game.menus);
		InitUI(game.ui, game.resources);
		SetGameState(game, GameState::MainMenu);
	}

	void HandleImputAndEvents(Game &game, const sf::Event &event)
	{
		if (event.type == sf::Event::Closed)
		{
			SetGameState(game, GameState::Exit);
			return;
		}
		switch (game.gameState)
		{
		case GameState::MainMenu:
			HandleMenuImput(game, event);
			break;
		case GameState::GameLoop:
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				SetGameState(game, GameState::Pause);
			}
			HandleSnakeImput(game.snake, event);
			break;
		case GameState::Pause:
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				SetGameState(game, GameState::GameLoop);
			}
			HandleMenuImput(game, event);
			break;
		case GameState::GameOver:
			HandleMenuImput(game, event);
			break;
		default:
			break;
		}
	}

	void UpdateGame(Game &game, const float deltaTime)
	{
		switch (game.gameState)
		{
		case GameState::MainMenu:
			break;
		case GameState::GameLoop:
			UpdateGameLoop(game, deltaTime);
			break;
		default:
			break;
		}
	}

	void DrawGame(Game &game, sf::RenderTexture &texture)
	{
		switch (game.gameState)
		{
		case GameState::MainMenu:
			DrawMenuUI(game.ui, game.currentMenu, texture);
			break;
		case GameState::GameLoop:
			DrawLevel(game.level, texture);
			DrawSnake(game.snake, texture);
			break;
		case GameState::GameOver:
			DrawLevel(game.level, texture);
			DrawSnake(game.snake, texture);
			DrawMenuUI(game.ui, game.currentMenu, texture);
		case GameState::Pause:
			DrawLevel(game.level, texture);
			DrawSnake(game.snake, texture);
			DrawMenuUI(game.ui, game.currentMenu, texture);
		default:
			break;
		}
	}

	void DeinitializeGame(Game &game, sf::RenderWindow &window)
	{
		window.close();
	}

	void SetGameState(Game &game, const GameState &gameState)
	{
		switch (gameState)
		{
		case GameState::MainMenu:
			SetMenuState(game, MenuState::Main);
			break;
		case GameState::GameLoop:
			break;
		case GameState::Pause:
			SetMenuState(game, MenuState::Pause);
			break;
		case GameState::GameOver:
			SetMenuState(game, MenuState::GameOver);
			break;
		default:
			break;
		}
		game.gameState = gameState;
	}

	void SetMenuState(Game &game, const MenuState &menuState)
	{
		game.currentMenu = game.menus[menuState];
		game.currentMenu.selected = 0;
		UpdateMenuUI(game.ui, game.currentMenu);
	}

	void StartGameLoop(Game &game)
	{
		game.speed = INITIAL_SPEED;
		InitLevel(game.level, game.resources);
		InitSnake(game.snake, game.resources);
		for (int i = 0; i < game.snake.segments.size(); i++)
		{
			SetCellType(game.level, game.snake.segments[i].position, CellType::Snake);
		}
		SpawnApple(game.level);
	}

	void UpdateGameLoop(Game &game, const float deltaTime)
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
				SetCellType(game.level, snakeHead.position, CellType::Snake);
				UpdateCellColor(game.level, snakeHead.position);
				SpawnApple(game.level);
			}
			else
			{
				SetCellType(game.level, snakeTail.position, CellType::Empty);
				if (GetCellType(game.level, snakeHead.position) == CellType::Snake || GetCellType(game.level, snakeHead.position) == CellType::Wall)
				{
					SetGameState(game, GameState::GameOver);
				}
				else
				{
					SetCellType(game.level, snakeHead.position, CellType::Snake);
				}
			}
			bool isMouthOpen = CellsBetween(snakeHead.position, game.level.apple.position) <= 2;
			UpdateSnakeTexture(game.snake, isMouthOpen);
			timer -= interval;
		}
	}

	void HandleMenuImput(Game &game, const sf::Event &event)
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
		{
			game.currentMenu.selected -= 1;
			if (game.currentMenu.selected < 0)
			{
				game.currentMenu.selected = game.currentMenu.items.size() - 1;
			}
			UpdateSelectedItem(game.ui, game.currentMenu);
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
		{
			game.currentMenu.selected += 1;
			if (game.currentMenu.selected > game.currentMenu.items.size() - 1)
			{
				game.currentMenu.selected = 0;
			}
			UpdateSelectedItem(game.ui, game.currentMenu);
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
		{
			switch (game.currentMenu.items[game.currentMenu.selected].actionType)
			{
			case MenuActionType::SwitchGameState:
				SetGameState(game, static_cast<GameState>(game.currentMenu.items[game.currentMenu.selected].actionTarget));
				break;
			case MenuActionType::StartGame:
				SetGameState(game, GameState::GameLoop);
				StartGameLoop(game);
			default:
				break;
			}
		};
	}

}
