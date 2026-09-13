#include "Game.h"
#include <cmath>

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
			HandleLeaderboardImput(game, event);
			break;
		case GameState::Leaderboard:
			HandleMenuImput(game, event);
			HandleLeaderboardImput(game, event);
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
			UpdateMenuUI(game.ui, deltaTime);
			break;
		case GameState::LevelSelect:
			UpdateMenuUI(game.ui, deltaTime);
			UpdateLevelSelectUI(game.ui, deltaTime);
			break;
		case GameState::GameLoop:
			UpdateGameLoop(game, deltaTime);
			break;
		case GameState::GameOver:
			UpdateMenuUI(game.ui, deltaTime);
			break;
		case GameState::Delay:
			UpdateDelay(game, deltaTime);
			break;
		case GameState::Leaderboard:
			UpdateMenuUI(game.ui, deltaTime);
			break;
		case GameState::Pause:
			UpdateMenuUI(game.ui, deltaTime);
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
		case GameState::Leaderboard:
			DrawUITint(game.ui, texture);
			DrawLeaderboardUI(game.ui, game.leaderboard, texture);
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
			DrawLeaderboardUI(game.ui, game.leaderboard, texture);
			DrawMenuUI(game.ui, game.menuLayers.back(), texture);
			break;
		case GameState::Delay:
			DrawLevel(game.level, texture);
			DrawSnake(game.snake, texture);
			DrawHud(game.ui, texture);
			DrawUITint(game.ui, texture);
			DrawDelayUI(game.ui, texture);
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
			break;
		case GameState::GameLoop:
			PlayMusic(game);
			break;
		case GameState::Pause:
			SetMenuState(game, MenuState::Pause);
			PauseMusic(game);
			break;
		case GameState::GameOver:
			SetMenuState(game, MenuState::GameOver);
			LoadLeaderboardUI(game.ui, game.leaderboard, game.levelMangager);
			break;
		case GameState::Leaderboard:
			SetMenuState(game, MenuState::Leaderboard);
			LoadLeaderboard(game.leaderboard, game.levelMangager.levels[game.levelMangager.selected].id);
			LoadLeaderboardUI(game.ui, game.leaderboard, game.levelMangager);
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

		LoadMenuUI(game.ui, game.menuLayers.back());
	}

	void StartGameLoop(Game &game)
	{
		StopMusic(game);
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
				PlaySound(game.soundFX, game.resources.appleEaten);
			}
			else
			{
				SetCellType(game.level.config, snakeTail.position, CellType::Empty);
				if (GetCellType(game.level.config, snakeHead.position) == CellType::Snake || GetCellType(game.level.config, snakeHead.position) == CellType::Wall)
				{
					PlaySound(game.soundFX, game.resources.wall);
					PlaySound(game.soundJingle, game.resources.gameOver);
					isDead = true;
					if (game.score > 0)
					{
						AddLeaderboardEntry(game.leaderboard, game.config.playerName, game.score);
						SaveLeaderboard(game.leaderboard);
					}
					StopMusic(game);
					StartGameDelay(game, GameState::GameOver, DelayType::GameOver);
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
				LoadMenuUIItems(game.ui, game.menuLayers.back());
				enterHeld = true;
			}
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			if (game.menuLayers.size() > 1)
			{
				game.menuLayers.pop_back();
				LoadMenuUI(game.ui, game.menuLayers.back());
			}
			else if (game.gameState == GameState::Pause)
			{
				SetGameState(game, GameState::GameLoop);
			}
		}
		else if (!enterHeld && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
		{
			int previousItem = game.menuLayers.back().selected;
			game.menuLayers.back().selected -= 1;
			if (game.menuLayers.back().selected < 0)
			{
				game.menuLayers.back().selected = game.menuLayers.back().items.size() - 1;
			}
			SetMenuSelectedItem(game.ui, game.menuLayers.back());
			if (previousItem != game.menuLayers.back().selected)
			{
				PlaySound(game.soundFX, game.resources.uiMoveVertical);
			}
		}
		else if (!enterHeld && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
		{
			int previousItem = game.menuLayers.back().selected;
			game.menuLayers.back().selected += 1;
			if (game.menuLayers.back().selected > game.menuLayers.back().items.size() - 1)
			{
				game.menuLayers.back().selected = 0;
			}
			SetMenuSelectedItem(game.ui, game.menuLayers.back());
			if (previousItem != game.menuLayers.back().selected)
			{
				PlaySound(game.soundFX, game.resources.uiMoveVertical);
			}
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
					StartGameLoop(game);
					StartGameDelay(game, GameState::GameLoop, DelayType::Countdown);
					break;
				case MenuActionType::ResumeGame:
					StartGameDelay(game, GameState::GameLoop, DelayType::Countdown);
					break;
				case MenuActionType::PreviousMenu:
					if (game.menuLayers.size() > 1)
					{
						game.menuLayers.pop_back();
						LoadMenuUI(game.ui, game.menuLayers.back());
					}
					break;
				case MenuActionType::SetScreenScale:
					game.config.windowResolution = static_cast<WindowResolution>(game.menuLayers.back().items[game.menuLayers.back().selected].actionTarget);
					SaveConfig(game.config);
					SetRendererResolution(game.renderer, game.config.windowResolution);
					UpdateSubMenuItems(game.menuLayers.back(), game, static_cast<int>(game.config.windowResolution));
					LoadMenuUIItems(game.ui, game.menuLayers.back());
					break;
				case MenuActionType::SetDifficulty:
					game.config.difficulty = static_cast<GameDifficulty>(game.menuLayers.back().items[game.menuLayers.back().selected].actionTarget);
					SaveConfig(game.config);
					UpdateSubMenuItems(game.menuLayers.back(), game, static_cast<int>(game.config.difficulty));
					LoadMenuUIItems(game.ui, game.menuLayers.back());
					break;
				default:
					break;
				}
				PlaySound(game.soundFX, game.resources.uiSelect);
			}
		};
	}

	void HandleLevelSelectImput(Game &game, const sf::Event &event)
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
		{
			if (game.menuLayers.back().type != MenuType::SubMenu)
			{
				int previousItem = game.levelMangager.selected;
				game.levelMangager.selected -= 1;
				if (game.levelMangager.selected < 0)
				{
					game.levelMangager.selected = game.levelMangager.levels.size() - 1;
				}
				SetLevelSelectedItem(game.ui, game.levelMangager);
				if (previousItem != game.levelMangager.selected)
				{
					PlaySound(game.soundFX, game.resources.uiMoveHorizontal);
				}
			}
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
		{
			if (game.menuLayers.back().type != MenuType::SubMenu)
			{
				int previousItem = game.levelMangager.selected;
				game.levelMangager.selected += 1;
				if (game.levelMangager.selected > game.levelMangager.levels.size() - 1)
				{
					game.levelMangager.selected = 0;
				}
				SetLevelSelectedItem(game.ui, game.levelMangager);
				if (previousItem != game.levelMangager.selected)
				{
					PlaySound(game.soundFX, game.resources.uiMoveHorizontal);
				}
			}
		}
	}

	void HandleLeaderboardImput(Game &game, const sf::Event &event)
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
		{
			if (game.menuLayers.back().type != MenuType::SubMenu)
			{
				int previousItem = game.leaderboard.firstDisplayedItem;
				game.leaderboard.firstDisplayedItem -= LEADERBOARD_DISPLAYED;
				if (game.leaderboard.firstDisplayedItem < 0)
				{
					game.leaderboard.firstDisplayedItem = ((game.leaderboard.entries.size() - 1) / LEADERBOARD_DISPLAYED) * LEADERBOARD_DISPLAYED;
				}
				LoadLeaderboardUI(game.ui, game.leaderboard, game.levelMangager);
				if (previousItem != game.leaderboard.firstDisplayedItem)
				{
					PlaySound(game.soundFX, game.resources.uiMoveHorizontal);
				}
			}
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
		{
			if (game.menuLayers.back().type != MenuType::SubMenu)
			{
				int previousItem = game.leaderboard.firstDisplayedItem;
				game.leaderboard.firstDisplayedItem += LEADERBOARD_DISPLAYED;
				if (game.leaderboard.firstDisplayedItem > game.leaderboard.entries.size() - 1)
				{
					game.leaderboard.firstDisplayedItem = 0;
				}
				LoadLeaderboardUI(game.ui, game.leaderboard, game.levelMangager);
				if (previousItem != game.leaderboard.firstDisplayedItem)
				{
					PlaySound(game.soundFX, game.resources.uiMoveHorizontal);
				}
			}
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

	void PlaySound(sf::Sound &sound, const GameSound &gameSound)
	{
		sound.setVolume(gameSound.volume);
		sound.setBuffer(gameSound.buffer);
		sound.play();
	}

	void PlayMusic(Game &game)
	{
		game.resources.music.play();
	}

	void PauseMusic(Game &game)
	{
		game.resources.music.pause();
	}

	void StopMusic(Game &game)
	{
		game.resources.music.stop();
	}

	void StartGameDelay(Game &game, GameState nextState, DelayType type)
	{
		SetGameState(game, GameState::Delay);
		game.delay.timer = 0.f;
		game.delay.nextState = nextState;
		game.delay.type = type;
		switch (type)
		{
		case DelayType::Countdown:
			game.delay.duration = DELAY_COUNTDOWN;
			break;
		case DelayType::GameOver:
			game.delay.duration = DELAY_GAME_OVER;
			break;
		default:
			break;
		}
	}

	void UpdateDelay(Game &game, const float deltaTime)
	{
		float timeLeft = game.delay.duration - game.delay.timer;

		static int wholeNumber = 0;
		switch (game.delay.type)
		{
		case DelayType::Countdown:
			if ((int)std::round(timeLeft) != wholeNumber)
			{
				wholeNumber = (int)std::round(timeLeft);
				if (wholeNumber == 0)
				{
					SetDelayUIText(game.ui, "Go!");
					PlaySound(game.soundFX, game.resources.countdownGo);
				}
				else
				{
					SetDelayUIText(game.ui, std::to_string(wholeNumber));
					PlaySound(game.soundFX, game.resources.countdown);
				}
			}
			break;
		case DelayType::GameOver:
			SetDelayUIText(game.ui, "GAME OVER!");
			break;
		default:
			break;
		}

		game.delay.timer += deltaTime;
		if (game.delay.timer >= game.delay.duration)
		{
			SetGameState(game, game.delay.nextState);
			wholeNumber = 0;
		}
	}

}
