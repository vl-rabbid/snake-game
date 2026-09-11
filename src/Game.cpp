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
		InitConfig(game.config);

		float gameHeight = (LEVEL_HEIGHT + HUD_HEIGHT) * CELL_SIZE;
		float gameWidth = LEVEL_WIDTH * CELL_SIZE;
		InitRenderer(game.renderer, gameWidth, gameHeight);
		SetRendererResolution(game.renderer, game.config.windowResolution);

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
			DrawMenuUI(game.ui, game.menuLayers.back(), texture);
			break;
		case GameState::GameLoop:
			DrawLevel(game.level, texture);
			DrawSnake(game.snake, texture);
			DrawHud(game.ui, texture);
			break;
		case GameState::GameOver:
			DrawLevel(game.level, texture);
			DrawSnake(game.snake, texture);
			DrawHud(game.ui, texture);
			DrawMenuUI(game.ui, game.menuLayers.back(), texture);
		case GameState::Pause:
			DrawLevel(game.level, texture);
			DrawSnake(game.snake, texture);
			DrawHud(game.ui, texture);
			DrawMenuUI(game.ui, game.menuLayers.back(), texture);
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
		game.menuLayers.clear();
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

	void SetMenuState(Game &game, MenuState menuState)
	{
		Menu menu;
		menu = game.menus[menuState];
		menu.selected = 0;
		menu.firstDisplayedItem = 0;
		game.menuLayers.push_back(menu);
		UpdateMenuLayer(game);
	}

	void UpdateMenuLayer(Game &game)
	{
		UpdateMenuUI(game.ui, game.menuLayers.back());
		UpdateMenuSelectedItem(game.ui, game.menuLayers.back());
	}

	void StartGameLoop(Game &game)
	{
		game.speed = static_cast<float>(game.config.difficulty);
		InitLevel(game.level, game.resources);
		LoadLeaderboard(game.leaderboard, game.level.config.id);
		InitSnake(game.snake, game.resources, game.level.config.snakeSpawn, game.level.config.snakeSize, game.level.countEmptyCells);
		for (int i = 0; i < game.snake.segments.size(); i++)
		{
			SetCellType(game.level, game.snake.segments[i].position, CellType::Snake);
		}
		SpawnApple(game.level);
		game.score = 0;
		UpdateHud(game.ui, game.level.config.name, game.score);
	}

	void UpdateGameLoop(Game &game, const float deltaTime)
	{
		static float timer = 0.f;
		float interval = 1.f / game.speed;

		timer += deltaTime;
		if (timer >= interval)
		{
			bool isDead = false;

			SnakeSegment snakeTail = game.snake.segments.back();
			UpdateSnake(game.snake);
			SnakeSegment snakeHead = game.snake.segments.front();

			if (GetCellType(game.level, snakeHead.position) == CellType::Apple)
			{
				AddSnakeSegment(game.snake, snakeTail);
				SetCellType(game.level, snakeHead.position, CellType::Snake);
				game.score += GetScoreMultiplier(game.config.difficulty);
				UpdateHud(game.ui, game.level.config.name, game.score);
				if (game.snake.segments.size() < game.level.countEmptyCells)
				{
					SpawnApple(game.level);
				}
			}
			else
			{
				SetCellType(game.level, snakeTail.position, CellType::Empty);
				if (GetCellType(game.level, snakeHead.position) == CellType::Snake || GetCellType(game.level, snakeHead.position) == CellType::Wall)
				{
					SetGameState(game, GameState::GameOver);
					isDead = true;
					if (game.score > 0)
					{
						AddLeaderboardEntry(game.leaderboard, game.config.playerName, game.score);
						SaveLeaderboard(game.leaderboard);
					}
				}
				else
				{
					SetCellType(game.level, snakeHead.position, CellType::Snake);
				}
			}
			bool isMouthOpen = CellsBetween(snakeHead.position, game.level.apple.position) <= 2;
			UpdateSnakeTexture(game.snake, isDead, isMouthOpen);
			timer -= interval;
		}
	}

	void HandleMenuImput(Game &game, const sf::Event &event)
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			if (game.menuLayers.size() > 1)
			{
				game.menuLayers.pop_back();
				UpdateMenuLayer(game);
			}
			else if (game.gameState == GameState::Pause)
			{
				SetGameState(game, GameState::GameLoop);
			}
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
		{
			game.menuLayers.back().selected -= 1;
			if (game.menuLayers.back().selected < 0)
			{
				game.menuLayers.back().selected = game.menuLayers.back().items.size() - 1;
			}
			UpdateMenuSelectedItem(game.ui, game.menuLayers.back());
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
		{
			game.menuLayers.back().selected += 1;
			if (game.menuLayers.back().selected > game.menuLayers.back().items.size() - 1)
			{
				game.menuLayers.back().selected = 0;
			}
			UpdateMenuSelectedItem(game.ui, game.menuLayers.back());
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
		{
			switch (game.menuLayers.back().items[game.menuLayers.back().selected].actionType)
			{
			case MenuActionType::SwitchGameState:
				SetGameState(game, static_cast<GameState>(game.menuLayers.back().items[game.menuLayers.back().selected].actionTarget));
				break;
			case MenuActionType::SwitchMenuState:
				SetMenuState(game, static_cast<MenuState>(game.menuLayers.back().items[game.menuLayers.back().selected].actionTarget));
				break;
			case MenuActionType::StartGame:
				SetGameState(game, GameState::GameLoop);
				StartGameLoop(game);
				break;
			case MenuActionType::PreviousMenu:
				if (game.menuLayers.size() > 1)
				{
					game.menuLayers.pop_back();
					UpdateMenuLayer(game);
				}
				break;
			case MenuActionType::SetScreenScale:
				game.config.windowResolution = static_cast<WindowResolution>(game.menuLayers.back().items[game.menuLayers.back().selected].actionTarget);
				SaveConfig(game.config);
				SetRendererResolution(game.renderer, game.config.windowResolution);
				break;
			case MenuActionType::SetDifficulty:
				game.config.difficulty = static_cast<GameDifficulty>(game.menuLayers.back().items[game.menuLayers.back().selected].actionTarget);
				SaveConfig(game.config);
				if (game.menuLayers.size() > 1)
				{
					game.menuLayers.pop_back();
					UpdateMenuLayer(game);
				}
				break;
			default:
				break;
			}
		};
	}

	int GetScoreMultiplier(GameDifficulty gameDifficulty)
	{
		switch (gameDifficulty)
		{
		case GameDifficulty::VeryEasy:
			return 2;
		case GameDifficulty::Easy:
			return 4;
		case GameDifficulty::Normal:
			return 6;
		case GameDifficulty::Hard:
			return 8;
		case GameDifficulty::VeryHard:
			return 10;
		default:
			break;
		}
		return 1;
	}

}
