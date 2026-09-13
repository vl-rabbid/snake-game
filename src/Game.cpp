#include "Game.h"

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
		game.background.setTexture(game.resources.background);
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
		case GameState::LevelSelect:
			HandleMenuImput(game, event);
			HandleLevelSelectImput(game, event);
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
		texture.draw(game.background);
		switch (game.gameState)
		{
		case GameState::MainMenu:
			DrawUITint(game.ui, texture);
			DrawMenuUI(game.ui, game.menuLayers.back(), texture);
			break;
		case GameState::LevelSelect:
			DrawUITint(game.ui, texture);
			DrawLevelSelect(game.ui, game.levelMangager, texture);
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
			DrawUITint(game.ui, texture);
			DrawMenuUI(game.ui, game.menuLayers.back(), texture);
			break;
		case GameState::Pause:
			DrawLevel(game.level, texture);
			DrawSnake(game.snake, texture);
			DrawHud(game.ui, texture);
			DrawUITint(game.ui, texture);
			DrawMenuUI(game.ui, game.menuLayers.back(), texture);
			break;
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
		case GameState::LevelSelect:
			SetMenuState(game, MenuState::LevelSelect);
			LoadLevelManager(game.levelMangager);
			LoadLevelSelectUI(game.ui, game.levelMangager);
			UpdateLevelSelectedItem(game.ui, game.levelMangager);
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

		if (menuState == MenuState::Resolution)
		{
			UpdateSubMenuItems(game.menuLayers.back(), game, static_cast<int>(game.config.windowResolution));
		}
		else if (menuState == MenuState::Difficulty)
		{
			UpdateSubMenuItems(game.menuLayers.back(), game, static_cast<int>(game.config.difficulty));
		}

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
		game.level.config = game.levelMangager.levels[game.levelMangager.selected];
		InitLevel(game.level, game.resources);
		LoadLeaderboard(game.leaderboard, game.level.config.id);
		InitSnake(game.snake, game.resources, game.level.config.snakeSpawn, game.level.config.snakeSize, game.level.countEmptyCells);
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

			if (GetCellType(game.level.config, snakeHead.position) == CellType::Apple)
			{
				AddSnakeSegment(game.snake, snakeTail);
				SetCellType(game.level.config, snakeHead.position, CellType::Snake);
				game.score += GetScoreMultiplier(game.config.difficulty);
				UpdateHud(game.ui, game.level.config.name, game.score);
				if (game.snake.segments.size() < game.level.countEmptyCells)
				{
					SpawnApple(game.level);
				}
			}
			else
			{
				SetCellType(game.level.config, snakeTail.position, CellType::Empty);
				if (GetCellType(game.level.config, snakeHead.position) == CellType::Snake || GetCellType(game.level.config, snakeHead.position) == CellType::Wall)
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
					SetCellType(game.level.config, snakeHead.position, CellType::Snake);
				}
			}
			bool isMouthOpen = CellsBetween(snakeHead.position, game.level.apple.position) <= 2;
			UpdateSnakeTexture(game.snake, isDead, isMouthOpen);
			timer -= interval;
		}
	}

	void HandleMenuImput(Game &game, const sf::Event &event)
	{
		static bool enterHeld = false;
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
		{
			if (!game.menuLayers.back().items[game.menuLayers.back().selected].pressed)
			{
				game.menuLayers.back().items[game.menuLayers.back().selected].pressed = true;
				UpdateMenuLayer(game);
				enterHeld = true;
			}
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
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
		else if (!enterHeld && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
		{
			game.menuLayers.back().selected -= 1;
			if (game.menuLayers.back().selected < 0)
			{
				game.menuLayers.back().selected = game.menuLayers.back().items.size() - 1;
			}
			UpdateMenuSelectedItem(game.ui, game.menuLayers.back());
		}
		else if (!enterHeld && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
		{
			game.menuLayers.back().selected += 1;
			if (game.menuLayers.back().selected > game.menuLayers.back().items.size() - 1)
			{
				game.menuLayers.back().selected = 0;
			}
			UpdateMenuSelectedItem(game.ui, game.menuLayers.back());
		}
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
		{
			enterHeld = false;
			game.menuLayers.back().items[game.menuLayers.back().selected].pressed = false;
			if (game.menuLayers.back().items[game.menuLayers.back().selected].enabled)
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
					UpdateSubMenuItems(game.menuLayers.back(), game, static_cast<int>(game.config.windowResolution));
					UpdateMenuLayer(game);
					break;
				case MenuActionType::SetDifficulty:
					game.config.difficulty = static_cast<GameDifficulty>(game.menuLayers.back().items[game.menuLayers.back().selected].actionTarget);
					SaveConfig(game.config);
					UpdateSubMenuItems(game.menuLayers.back(), game, static_cast<int>(game.config.difficulty));
					UpdateMenuLayer(game);
					break;
				default:
					break;
				}
			}
		};
	}

	void HandleLevelSelectImput(Game &game, const sf::Event &event)
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
		{
			game.levelMangager.selected -= 1;
			if (game.levelMangager.selected < 0)
			{
				game.levelMangager.selected = game.levelMangager.levels.size() - 1;
			}
			UpdateLevelSelectedItem(game.ui, game.levelMangager);
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
		{
			game.levelMangager.selected += 1;
			if (game.levelMangager.selected > game.levelMangager.levels.size() - 1)
			{
				game.levelMangager.selected = 0;
			}
			UpdateLevelSelectedItem(game.ui, game.levelMangager);
		}
	}

	void UpdateSubMenuItems(Menu &menu, Game &game, int actionTarget)
	{
		for (int i = 0; i < menu.items.size(); i++)
		{
			if (menu.items[i].actionTarget == actionTarget)
			{
				menu.items[i].enabled = false;
			}
			else
			{
				menu.items[i].enabled = true;
			}
		}
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
