#include "Game.h"
#include <cmath>

namespace SnakeGame
{
	ApplicationRequest GetApplicationRequest(Game &game)
	{
		ApplicationRequest request = game.applicationRequest;
		game.applicationRequest = {ApplicationRequestType::None};
		return request;
	}

	void InitGame(Game &game)
	{
		int seed = (int)time(nullptr);
		srand(seed);

		InitResources(game.resources);
		game.background.setTexture(game.resources.background);
		InitConfig(game.config);

		InitMenues(game.menus);
		InitUI(game.ui, game.resources);
		SetGameState(game, GameState::Menu);
		SetMenuState(game, MenuState::Main);

		game.hud.Init(game.resources);
		game.levelMangager.Init(game.resources);
		game.leaderboardManager.Init(game.resources);
	}

	void HandleGameImput(Game &game, const sf::Event &event)
	{
		if (event.type == sf::Event::Closed)
		{
			game.applicationRequest = {ApplicationRequestType::ExitApplication};
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
			game.snake.HandleInput(event);
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
			game.level.Draw(texture);
			game.snake.Draw(texture);
			game.hud.Draw(texture);
			break;
		case GameState::Delay:
			game.level.Draw(texture);
			game.snake.Draw(texture);
			game.hud.Draw(texture);
			game.hud.DrawDelay(texture);
			break;
		default:
			break;
		}
	}

	void DeinitializeGame(Game &game)
	{
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

		Leaderboard leaderboard;

		switch (game.menuLayers.back().state)
		{
		case MenuState::LevelSelect:
			game.levelMangager.LoadFromFiles();
			break;
		case MenuState::Pause:
			PauseMusic(game);
			break;
		case MenuState::GameOver:
			game.leaderboardManager.LoadUI(game.leaderboard);
			break;
		case MenuState::Leaderboard:
			leaderboard.LoadFromFile(game.levelMangager.GetSelectedLevelConfig());
			game.leaderboardManager.LoadUI(leaderboard);
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

	void StartGameLoop(Game &game, const LevelConfig &levelConfig)
	{
		game.level.Init(levelConfig, game.resources);
		game.leaderboard.LoadFromFile(levelConfig);
		ResetGameLoop(game);
	}

	void ResetGameLoop(Game &game)
	{
		StopMusic(game);
		game.level.ResetState();
		game.speed = static_cast<float>(game.config.difficulty);
		game.snake.Reset(game.resources, game.level.GetSnakeSpawn(), game.level.GetSnakeSize(), game.level.GetMaxSnakeLength());
		game.level.SpawnApple();
		game.score = 0;
		game.hud.Update(game.level.GetName(), game.score);
	}

	void UpdateGameLoop(Game &game, const float deltaTime)
	{
		static float timer = 0.f;
		float interval = 1.f / game.speed;

		timer += deltaTime;
		if (timer >= interval)
		{
			bool isDead = false;

			Position2D oldTailPosition = game.snake.GetTailPosition();
			game.snake.UpdatePosition();
			Position2D headPosition = game.snake.GetHeadPosition();

			if (game.level.GetState(headPosition) == CellType::Apple)
			{
				game.snake.Grow(game.resources);
				game.level.SetState(headPosition, CellType::Snake);
				game.score += GetScoreMultiplier(game.config.difficulty);
				game.hud.Update(game.level.GetName(), game.score);
				if (game.snake.GetLength() < game.level.GetMaxSnakeLength())
					game.level.SpawnApple();
				PlaySound(game, game.soundFX, game.resources.appleEaten);
			}
			else
			{
				game.level.SetState(oldTailPosition, CellType::Empty);
				if (game.level.GetState(headPosition) == CellType::Snake || game.level.GetState(headPosition) == CellType::Wall)
				{
					PlaySound(game, game.soundFX, game.resources.wall);
					PlaySound(game, game.soundJingle, game.resources.gameOver);
					isDead = true;
					if (game.score > 0)
						game.leaderboard.AddEntry(game.config.playerName, game.score);

					StopMusic(game);
					StartMenuStateDelay(game, MenuState::GameOver, DelayType::GameOver);
				}
				else
				{
					game.level.SetState(headPosition, CellType::Snake);
				}
			}
			bool isMouthOpen = CellsBetween(headPosition, game.level.GetApplePosition()) <= 2;
			game.snake.UpdateSprites(isDead, isMouthOpen);
			timer -= interval;
		}
	}

	void DrawMenu(Game &game, Menu &menu, sf::RenderTexture &texture)
	{
		switch (menu.state)
		{
		case MenuState::LevelSelect:
			DrawUITint(game.ui, texture);
			game.levelMangager.Draw(texture);
			DrawMenuUI(game.ui, menu, texture);
			break;
		case MenuState::Leaderboard:
			DrawUITint(game.ui, texture);
			game.leaderboardManager.Draw(texture);
			DrawMenuUI(game.ui, menu, texture);
			break;
		case MenuState::GameOver:
			game.level.Draw(texture);
			game.snake.Draw(texture);
			game.hud.Draw(texture);
			DrawUITint(game.ui, texture);
			game.leaderboardManager.Draw(texture);
			DrawMenuUI(game.ui, menu, texture);
			break;
		case MenuState::Pause:
			game.level.Draw(texture);
			game.snake.Draw(texture);
			game.hud.Draw(texture);
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
			game.levelMangager.Update(deltaTime);
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
			game.leaderboardManager.HandleInput(event);
			HandleMainMenuImput(game, event);
			break;
		case MenuState::LevelSelect:
			game.levelMangager.HandleInput(event);
			HandleMainMenuImput(game, event);
			break;
		case MenuState::GameOver:
			game.leaderboardManager.HandleInput(event);
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
					StartGameLoop(game, game.levelMangager.GetSelectedLevelConfig());
					StartGameStateDelay(game, GameState::GameLoop, DelayType::GameStart);
					break;
				case MenuActionType::ResetGame:
					ResetGameLoop(game);
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
					game.applicationRequest = {ApplicationRequestType::SetWindowScale};
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
				case MenuActionType::ExitApplication:
					game.applicationRequest = {ApplicationRequestType::ExitApplication};
					break;
				default:
					break;
				}
				PlaySound(game, game.soundFX, game.resources.uiSelect);
			}
		};
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
					game.hud.SetDelayText("Go!");
					PlaySound(game, game.soundFX, game.resources.countdownGo);
				}
				else
				{
					game.hud.SetDelayText(std::to_string(wholeNumber));
					PlaySound(game, game.soundFX, game.resources.countdown);
				}
			}
			break;
		case DelayType::GameOver:
			game.hud.SetDelayText("GAME OVER!");
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

	float GetGameWindowScale(Game &game)
	{
		return static_cast<float>(game.config.windowResolution);
	}
}
