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
		SetGameState(game, GameState::Menu);
		SetMenuState(game, MenuState::Main);
	}

	void HandleGameImput(Game &game, const sf::Event &event)
	{
		if (event.type == sf::Event::Closed)
		{
			SetGameState(game, GameState::Exit);
			return;
		}
		switch (game.gameState)
		{
		case GameState::Menu:
			HandleMenuImput(game, event);
			break;
		case GameState::GameLoop:
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				SetGameState(game, GameState::Menu);
				SetMenuState(game, MenuState::Pause);
			}
			HandleSnakeImput(game.snake, event);
			break;
		default:
			break;
		}
	}

	void UpdateGame(Game &game, const float deltaTime)
	{
		switch (game.gameState)
		{
		case GameState::Menu:
			UpdateMenu(game, deltaTime);
			break;
		case GameState::GameLoop:
			UpdateGameLoop(game, deltaTime);
			break;
		case GameState::Delay:
			UpdateDelay(game, deltaTime);
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
		case GameState::Menu:
			if (game.menuLayers.back().type == MenuType::FullMenu)
			{
				DrawMenu(game, game.menuLayers.back(), texture);
			}
			else if (game.menuLayers.size() > 1)
			{
				if (game.menuLayers.back().type == MenuType::SubMenu || game.menuLayers.back().type == MenuType::InputString)
				{
					DrawMenu(game, game.menuLayers[game.menuLayers.size() - 2], texture);
					DrawMenu(game, game.menuLayers.back(), texture);
				}
			}
			break;
		case GameState::GameLoop:
			DrawLevel(game.level, texture);
			DrawSnake(game.snake, texture);
			DrawHud(game.ui, texture);
			break;
		case GameState::Delay:
			DrawLevel(game.level, texture);
			DrawSnake(game.snake, texture);
			DrawHud(game.ui, texture);
			DrawUITint(game.ui, texture);
			DrawDelayUI(game.ui, texture);
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
		switch (gameState)
		{
		case GameState::GameLoop:
			game.menuLayers.clear();
			PlayMusic(game);
			break;
		default:
			break;
		}
		game.gameState = gameState;
	}

	void SetMenuState(Game &game, MenuState menuState)
	{
		if (menuState == MenuState::Main)
		{
			game.menuLayers.clear();
		}

		Menu menu;
		menu = game.menus[menuState];
		menu.selected = 0;
		menu.firstDisplayedItem = 0;
		game.menuLayers.push_back(menu);

		switch (game.menuLayers.back().state)
		{
		case MenuState::LevelSelect:
			LoadLevelManager(game.levelMangager);
			LoadLevelSelectUI(game.ui, game.levelMangager);
			break;
		case MenuState::Pause:
			PauseMusic(game);
			break;
		case MenuState::GameOver:
			LoadLeaderboardUI(game.ui, game.leaderboard, game.levelMangager);
			break;
		case MenuState::Leaderboard:
			LoadLeaderboard(game.leaderboard, game.levelMangager.levels[game.levelMangager.selected].id);
			LoadLeaderboardUI(game.ui, game.leaderboard, game.levelMangager);
			break;
		case MenuState::Resolution:
			SetSubMenuItems(game.menuLayers.back(), game, static_cast<int>(game.config.windowResolution));
			break;
		case MenuState::Difficulty:
			SetSubMenuItems(game.menuLayers.back(), game, static_cast<int>(game.config.difficulty));
			break;
		case MenuState::Settings:
			SetSettingsItems(game.menuLayers.back(), game);
			break;
		case MenuState::SetPlayerName:
			game.newPlayerName = game.config.playerName;
			SetInputLabel(game.ui, game.newPlayerName);
			break;
		default:
			break;
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
				PlaySound(game, game.soundFX, game.resources.appleEaten);
			}
			else
			{
				SetCellType(game.level.config, snakeTail.position, CellType::Empty);
				if (GetCellType(game.level.config, snakeHead.position) == CellType::Snake || GetCellType(game.level.config, snakeHead.position) == CellType::Wall)
				{
					PlaySound(game, game.soundFX, game.resources.wall);
					PlaySound(game, game.soundJingle, game.resources.gameOver);
					isDead = true;
					if (game.score > 0)
					{
						AddLeaderboardEntry(game.leaderboard, game.config.playerName, game.score);
						SaveLeaderboard(game.leaderboard);
					}
					StopMusic(game);
					StartMenuStateDelay(game, MenuState::GameOver, DelayType::GameOver);
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

	void DrawMenu(Game &game, Menu &menu, sf::RenderTexture &texture)
	{
		switch (menu.state)
		{
		case MenuState::LevelSelect:
			DrawUITint(game.ui, texture);
			DrawLevelSelect(game.ui, game.levelMangager, texture);
			DrawMenuUI(game.ui, menu, texture);
			break;
		case MenuState::Leaderboard:
			DrawUITint(game.ui, texture);
			DrawLeaderboardUI(game.ui, game.leaderboard, texture);
			DrawMenuUI(game.ui, menu, texture);
			break;
		case MenuState::GameOver:
			DrawLevel(game.level, texture);
			DrawSnake(game.snake, texture);
			DrawHud(game.ui, texture);
			DrawUITint(game.ui, texture);
			DrawLeaderboardUI(game.ui, game.leaderboard, texture);
			DrawMenuUI(game.ui, menu, texture);
			break;
		case MenuState::Pause:
			DrawLevel(game.level, texture);
			DrawSnake(game.snake, texture);
			DrawHud(game.ui, texture);
			DrawUITint(game.ui, texture);
			DrawMenuUI(game.ui, menu, texture);
			break;
		default:
			DrawUITint(game.ui, texture);
			DrawMenuUI(game.ui, menu, texture);
			break;
		}
	}

	void UpdateMenu(Game &game, const float deltaTime)
	{
		switch (game.menuLayers.back().state)
		{
		case MenuState::LevelSelect:
			UpdateMenuUI(game.ui, deltaTime);
			UpdateLevelSelectUI(game.ui, deltaTime);
			break;
		case MenuState::SetPlayerName:
			UpdateInputMarker(game.ui, deltaTime);
			UpdateMenuUI(game.ui, deltaTime);
			break;
		default:
			UpdateMenuUI(game.ui, deltaTime);
			break;
		}
	}

	void HandleMenuImput(Game &game, const sf::Event &event)
	{
		switch (game.menuLayers.back().state)
		{
		case MenuState::Leaderboard:
			HandleLeaderboardImput(game, event);
			HandleMainMenuImput(game, event);
			break;
		case MenuState::LevelSelect:
			HandleLevelSelectImput(game, event);
			HandleMainMenuImput(game, event);
			break;
		case MenuState::GameOver:
			HandleLeaderboardImput(game, event);
			HandleMainMenuImput(game, event);
			break;
		case MenuState::SetPlayerName:
			HandleMainMenuImput(game, event);
			HandleTypingInput(game, event);
			break;
		default:
			HandleMainMenuImput(game, event);
			break;
		}
	}

	void HandleMainMenuImput(Game &game, const sf::Event &event)
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
				PlaySound(game, game.soundFX, game.resources.uiSelect);
			}
			else if (game.menuLayers.back().state == MenuState::Pause)
			{
				StartGameStateDelay(game, GameState::GameLoop, DelayType::GameStart);
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
				PlaySound(game, game.soundFX, game.resources.uiMoveVertical);
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
				PlaySound(game, game.soundFX, game.resources.uiMoveVertical);
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
					StartGameStateDelay(game, GameState::GameLoop, DelayType::GameStart);
					break;
				case MenuActionType::ResumeGame:
					StartGameStateDelay(game, GameState::GameLoop, DelayType::GameStart);
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
					SetSubMenuItems(game.menuLayers.back(), game, static_cast<int>(game.config.windowResolution));
					LoadMenuUIItems(game.ui, game.menuLayers.back());
					break;
				case MenuActionType::SetDifficulty:
					game.config.difficulty = static_cast<GameDifficulty>(game.menuLayers.back().items[game.menuLayers.back().selected].actionTarget);
					SaveConfig(game.config);
					SetSubMenuItems(game.menuLayers.back(), game, static_cast<int>(game.config.difficulty));
					LoadMenuUIItems(game.ui, game.menuLayers.back());
					break;
				case MenuActionType::ToggleSound:
					game.config.soundEnabled = !game.config.soundEnabled;
					SaveConfig(game.config);
					SetSettingsItems(game.menuLayers.back(), game);
					LoadMenuUIItems(game.ui, game.menuLayers.back());
					break;
				case MenuActionType::ToggleMusic:
					game.config.musicEnabled = !game.config.musicEnabled;
					SaveConfig(game.config);
					SetSettingsItems(game.menuLayers.back(), game);
					LoadMenuUIItems(game.ui, game.menuLayers.back());
					break;
				case MenuActionType::SavePlayerName:
					game.config.playerName = game.newPlayerName;
					SaveConfig(game.config);
					if (game.menuLayers.size() > 1)
					{
						game.menuLayers.pop_back();
						LoadMenuUI(game.ui, game.menuLayers.back());
					}
					break;
				default:
					break;
				}
				PlaySound(game, game.soundFX, game.resources.uiSelect);
			}
		};
	}

	void HandleLevelSelectImput(Game &game, const sf::Event &event)
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
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
					PlaySound(game, game.soundFX, game.resources.uiMoveHorizontal);
			}
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
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
				PlaySound(game, game.soundFX, game.resources.uiMoveHorizontal);
			}
		}
	}

	void HandleLeaderboardImput(Game &game, const sf::Event &event)
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
		{
			if (game.leaderboard.entries.size() > 0)
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
					PlaySound(game, game.soundFX, game.resources.uiMoveHorizontal);
				}
			}
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
		{
			if (game.leaderboard.entries.size() > 0)
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
					PlaySound(game, game.soundFX, game.resources.uiMoveHorizontal);
				}
			}
		}
	}

	void HandleTypingInput(Game &game, const sf::Event &event)
	{
		if (event.type == sf::Event::TextEntered)
		{
			char32_t c = event.text.unicode;
			if (c == '\b')
			{
				if (!game.newPlayerName.empty())
				{
					game.newPlayerName.pop_back();
					SetInputLabel(game.ui, game.newPlayerName);
					PlaySound(game, game.soundFX, game.resources.input);
					SetInputMenuItems(game.menuLayers.back(), game);
					LoadMenuUIItems(game.ui, game.menuLayers.back());
				}
			}
			else if (game.newPlayerName.size() < 10 && IsAllowedInputChar(c))
			{
				game.newPlayerName += static_cast<char>(c);
				SetInputLabel(game.ui, game.newPlayerName);
				PlaySound(game, game.soundFX, game.resources.input);
				SetInputMenuItems(game.menuLayers.back(), game);
				LoadMenuUIItems(game.ui, game.menuLayers.back());
			}
		}
	}

	void SetInputMenuItems(Menu &menu, Game &game)
	{
		for (int i = 0; i < menu.items.size(); i++)
		{
			if (menu.items[i].actionType == MenuActionType::SavePlayerName)
			{
				if (game.newPlayerName.empty())
					menu.items[i].enabled = false;
				else
					menu.items[i].enabled = true;
			}
		}
	}

	void SetSubMenuItems(Menu &menu, Game &game, int actionTarget)
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

	void SetSettingsItems(Menu &menu, Game &game)
	{
		for (int i = 0; i < menu.items.size(); i++)
		{
			switch (menu.items[i].actionType)
			{
			case MenuActionType::ToggleSound:
				if (game.config.soundEnabled)
					menu.items[i].label = "Sound: ON";
				else
					menu.items[i].label = "Sound: OFF";
				break;
			case MenuActionType::ToggleMusic:
				if (game.config.musicEnabled)
					menu.items[i].label = "Music: ON";
				else
					menu.items[i].label = "Music: OFF";
				break;
			default:
				break;
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

	void PlaySound(Game &game, sf::Sound &sound, const GameSound &gameSound)
	{
		if (game.config.soundEnabled)
		{
			sound.setVolume(gameSound.volume);
			sound.setBuffer(gameSound.buffer);
			sound.play();
		}
	}

	void PlayMusic(Game &game)
	{
		if (game.config.musicEnabled)
		{
			game.resources.music.play();
		}
	}

	void PauseMusic(Game &game)
	{
		game.resources.music.pause();
	}

	void StopMusic(Game &game)
	{
		game.resources.music.stop();
	}

	void StartGameStateDelay(Game &game, GameState nextGameState, DelayType type)
	{
		SetGameState(game, GameState::Delay);
		game.delay.timer = 0.f;
		game.delay.nextGameState = nextGameState;
		game.delay.type = type;
		switch (type)
		{
		case DelayType::GameStart:
			game.delay.duration = DELAY_COUNTDOWN;
			break;
		case DelayType::GameOver:
			game.delay.duration = DELAY_GAME_OVER;
			break;
		default:
			break;
		}
	}

	void StartMenuStateDelay(Game &game, MenuState nextMenuState, DelayType type)
	{
		SetGameState(game, GameState::Delay);
		game.delay.timer = 0.f;
		game.delay.nextMenuState = nextMenuState;
		game.delay.type = type;
		switch (type)
		{
		case DelayType::GameStart:
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
		case DelayType::GameStart:
			if ((int)std::round(timeLeft) != wholeNumber)
			{
				wholeNumber = (int)std::round(timeLeft);
				if (wholeNumber == 0)
				{
					SetDelayUIText(game.ui, "Go!");
					PlaySound(game, game.soundFX, game.resources.countdownGo);
				}
				else
				{
					SetDelayUIText(game.ui, std::to_string(wholeNumber));
					PlaySound(game, game.soundFX, game.resources.countdown);
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
			switch (game.delay.type)
			{
			case DelayType::GameStart:
				SetGameState(game, game.delay.nextGameState);
				break;
			case DelayType::GameOver:
				SetGameState(game, GameState::Menu);
				SetMenuState(game, game.delay.nextMenuState);
				break;
			default:
				break;
			}
			wholeNumber = 0;
		}
	}

	bool IsAllowedInputChar(char32_t c)
	{
		return (c >= U'A' && c <= U'Z') ||
			   (c >= U'a' && c <= U'z') ||
			   (c >= U'0' && c <= U'9') ||
			   c == U'_' ||
			   c == U'-';
	}
}
