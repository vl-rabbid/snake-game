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

		game.menu.Init(game.resources);
		SetGameState(game, GameState::Menu);
		game.menu.SetState(MenuState::Main, game.config, game.leaderboard);

		game.hud.Init(game.resources);
		game.audio.Init();
	}

	void HandleGameImput(Game &game, const sf::Event &event)
	{
		if (event.type == sf::Event::Closed)
		{
			game.applicationRequest = {ApplicationRequestType::ExitApplication};
			return;
		}
		MenuCommand command;
		switch (game.gameState)
		{
		case GameState::Menu:
			command = game.menu.HandleInput(event);
			HandleMenuCommand(game, command);
			break;
		case GameState::MenuOverlay:
			command = game.menu.HandleInput(event);
			HandleMenuCommand(game, command);
			break;
		case GameState::GameLoop:
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				SetGameState(game, GameState::MenuOverlay);
				game.menu.SetState(MenuState::Pause, game.config, game.leaderboard);
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
			game.menu.Update(deltaTime);
			break;
		case GameState::MenuOverlay:
			game.menu.Update(deltaTime);
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
			game.menu.Draw(texture);
			break;
		case GameState::MenuOverlay:
			game.level.Draw(texture);
			game.snake.Draw(texture);
			game.hud.Draw(texture);
			game.menu.Draw(texture);
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

	void SetGameState(Game &game, const GameState &gameState)
	{
		switch (gameState)
		{
		case GameState::Menu:
			game.audio.StopMusic();
			break;
		case GameState::MenuOverlay:
			game.audio.PauseMusic();
			break;
		case GameState::GameLoop:
			game.menu.ClearLayers();
			game.audio.PlayMusic(game.config.musicEnabled);
			break;
		default:
			break;
		}
		game.gameState = gameState;
	}

	void StartGameLoop(Game &game, const LevelConfig &levelConfig)
	{
		game.level.Init(levelConfig, game.resources);
		game.leaderboard.LoadFromFile(levelConfig);
		ResetGameLoop(game);
	}

	void ResetGameLoop(Game &game)
	{
		game.audio.StopMusic();
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
				game.audio.PlaySound(SoundID::AppleEaten, game.config.soundEnabled);
			}
			else
			{
				game.level.SetState(oldTailPosition, CellType::Empty);
				if (game.level.GetState(headPosition) == CellType::Snake || game.level.GetState(headPosition) == CellType::Wall)
				{
					game.audio.PlaySound(SoundID::Wall, game.config.soundEnabled);
					game.audio.PlaySound(SoundID::GameOver, game.config.soundEnabled);
					isDead = true;
					if (game.score > 0)
						game.leaderboard.AddEntry(game.config.playerName, game.score);

					game.audio.StopMusic();
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
					game.audio.PlaySound(SoundID::CountdownGo, game.config.soundEnabled);
				}
				else
				{
					game.audio.PlaySound(SoundID::Countdown, game.config.soundEnabled);
					game.hud.SetDelayText(std::to_string(wholeNumber));
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
				SetGameState(game, GameState::MenuOverlay);
				game.menu.SetState(game.delay.nextMenuState, game.config, game.leaderboard);
				break;
			default:
				break;
			}
			wholeNumber = 0;
		}
	}

	float GetGameWindowScale(Game &game)
	{
		return static_cast<float>(game.config.windowResolution);
	}

	void HandleMenuCommand(Game &game, MenuCommand &command)
	{
		switch (command.action)
		{
		case MenuAction::SwitchGameState:
			SetGameState(game, static_cast<GameState>(command.actionTarget));
			break;
		case MenuAction::SwitchMenuState:
			if (static_cast<MenuState>(command.actionTarget) == MenuState::Main)
				SetGameState(game, GameState::Menu);
			game.menu.SetState(static_cast<MenuState>(command.actionTarget), game.config, game.leaderboard);
			break;
		case MenuAction::StartGame:
			StartGameLoop(game, command.levelConfig);
			StartGameStateDelay(game, GameState::GameLoop, DelayType::GameStart);
			break;
		case MenuAction::ResetGame:
			ResetGameLoop(game);
			StartGameStateDelay(game, GameState::GameLoop, DelayType::GameStart);
			break;
		case MenuAction::ResumeGame:
			StartGameStateDelay(game, GameState::GameLoop, DelayType::GameStart);
			break;
		case MenuAction::SetScreenScale:
			game.config.windowResolution = static_cast<WindowResolution>(command.actionTarget);
			SaveConfig(game.config);
			game.applicationRequest = {ApplicationRequestType::SetWindowScale};
			game.menu.SetMenuItems(game.config);
			break;
		case MenuAction::SetDifficulty:
			game.config.difficulty = static_cast<GameDifficulty>(command.actionTarget);
			SaveConfig(game.config);
			game.menu.SetMenuItems(game.config);
			break;
		case MenuAction::ToggleSound:
			game.config.soundEnabled = !game.config.soundEnabled;
			SaveConfig(game.config);
			game.menu.SetMenuItems(game.config);
			break;
		case MenuAction::ToggleMusic:
			game.config.musicEnabled = !game.config.musicEnabled;
			SaveConfig(game.config);
			game.menu.SetMenuItems(game.config);
			break;
		case MenuAction::SavePlayerName:
			game.config.playerName = command.inputString;
			SaveConfig(game.config);
			break;
		case MenuAction::ExitApplication:
			game.applicationRequest = {ApplicationRequestType::ExitApplication};
			break;
		default:
			break;
		}
		game.menu.ReloadUI(command.setSelector, command.loadButtons, command.loadMenu, command.previousMenu);
		game.audio.PlaySound(command.sound, game.config.soundEnabled);
	}
}
