#include "Game/Game.h"
#include <cmath>
#include <iostream>

namespace SnakeGame
{
	Game::Game()
	{
		int seed = (int)time(nullptr);
		srand(seed);

		InitResources(resources);
		InitConfig(config);
		audio.Init();
		menu.Init(resources);
		SetState(GameState::Menu);
		menu.SetState(MenuState::Main, config, leaderboard);

		hud.Init(resources);
		background.setTexture(resources.background);
	}

	void Game::Update(const float deltaTime)
	{
		switch (state)
		{
		case GameState::Menu:
			menu.Update(deltaTime);
			break;
		case GameState::MenuOverlay:
			menu.Update(deltaTime);
			break;
		case GameState::GameLoop:
			UpdateGame(deltaTime);
			break;
		case GameState::Delay:
			UpdateDelay(deltaTime);
			break;
		default:
			break;
		}
	}

	void Game::Draw(sf::RenderTexture &texture) const
	{
		texture.draw(background);
		switch (state)
		{
		case GameState::Menu:
			menu.Draw(texture);
			break;
		case GameState::MenuOverlay:
			level.Draw(texture);
			snake.Draw(texture);
			hud.Draw(texture);
			menu.Draw(texture);
			break;
		case GameState::GameLoop:
			level.Draw(texture);
			snake.Draw(texture);
			hud.Draw(texture);
			break;
		case GameState::Delay:
			level.Draw(texture);
			snake.Draw(texture);
			hud.Draw(texture);
			hud.DrawDelay(texture);
			break;
		default:
			break;
		}
	}

	void Game::HandleInput(const sf::Event &event)
	{
		if (event.type == sf::Event::Closed)
		{
			request = {AppRequestType::ExitApplication};
			return;
		}

		MenuCommand command;
		switch (state)
		{
		case GameState::Menu:
			command = menu.HandleInput(event);
			HandleMenuCommand(command);
			break;
		case GameState::MenuOverlay:
			command = menu.HandleInput(event);
			HandleMenuCommand(command);
			break;
		case GameState::GameLoop:
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				SetState(GameState::MenuOverlay);
				menu.SetState(MenuState::Pause, config, leaderboard);
			}
			snake.HandleInput(event);
			break;
		default:
			break;
		}
	}

	AppRequest Game::ConsumeAppRequest()
	{
		AppRequest appRequest = request;
		request = {AppRequestType::None};
		return appRequest;
	}

	float Game::GetWindowScale()
	{
		return static_cast<float>(config.windowResolution);
	}

	void Game::SetState(const GameState &gameState)
	{
		switch (gameState)
		{
		case GameState::Menu:
			audio.StopMusic();
			break;
		case GameState::MenuOverlay:
			audio.PauseMusic();
			break;
		case GameState::GameLoop:
			menu.ClearLayers();
			audio.PlayMusic(config.musicEnabled);
			break;
		default:
			break;
		}
		state = gameState;
	}

	void Game::StartGame(const LevelConfig &levelConfig)
	{
		level.Init(levelConfig, resources);
		leaderboard.LoadFromFile(levelConfig);
		ResetGame();
	}

	void Game::ResetGame()
	{
		audio.StopMusic();
		level.ResetState();
		speed = static_cast<float>(config.difficulty);
		SetScoreMultiplier();
		snake.Reset(resources, level.GetSnakeSpawn(), level.GetSnakeSize(), level.GetMaxSnakeLength());
		level.SpawnApple();
		score = 0;
		hud.Update(level.GetName(), score);
	}

	void Game::UpdateGame(const float deltaTime)
	{
		static float timer = 0.f;
		float interval = 1.f / speed;

		timer += deltaTime;
		if (timer >= interval)
		{
			bool isDead = false;
			Position2D oldTailPosition = snake.GetTailPosition();
			snake.UpdatePosition();
			Position2D headPosition = snake.GetHeadPosition();

			if (level.GetState(headPosition) == CellType::Apple)
			{
				snake.Grow(resources);
				level.SetState(headPosition, CellType::Snake);
				score += scoreMultiplier;
				hud.Update(level.GetName(), score);
				if (snake.GetLength() < level.GetMaxSnakeLength())
					level.SpawnApple();
				audio.PlaySound(SoundID::AppleEaten, config.soundEnabled);
			}
			else
			{
				level.SetState(oldTailPosition, CellType::Empty);
				if (level.GetState(headPosition) == CellType::Snake || level.GetState(headPosition) == CellType::Wall)
				{
					audio.PlaySound(SoundID::Wall, config.soundEnabled);
					audio.PlaySound(SoundID::GameOver, config.soundEnabled);
					isDead = true;
					if (score > 0)
						leaderboard.AddEntry(config.playerName, score);

					audio.StopMusic();
					StartDelay(MenuState::GameOver, DelayType::GameOver);
				}
				else
				{
					level.SetState(headPosition, CellType::Snake);
				}
			}
			bool isMouthOpen = CellsBetween(headPosition, level.GetApplePosition()) <= 2;
			snake.UpdateSprites(isDead, isMouthOpen);
			timer -= interval;
		}
	}

	void Game::SetScoreMultiplier()
	{
		switch (config.difficulty)
		{
		case GameDifficulty::VeryEasy:
			scoreMultiplier = 2;
			break;
		case GameDifficulty::Easy:
			scoreMultiplier = 4;
			break;
		case GameDifficulty::Normal:
			scoreMultiplier = 6;
			break;
		case GameDifficulty::Hard:
			scoreMultiplier = 8;
			break;
		case GameDifficulty::VeryHard:
			scoreMultiplier = 10;
			break;
		default:
			break;
		}
	}

	void Game::HandleMenuCommand(const MenuCommand &command)
	{
		switch (command.action)
		{
		case MenuAction::MenuMoveVertical:
			menu.SetSelector();
			audio.PlaySound(SoundID::UIMoveVertical, config.soundEnabled);
			break;
		case MenuAction::MenuMoveHorizontal:
			audio.PlaySound(SoundID::UIMoveHorizontal, config.soundEnabled);
			break;
		case MenuAction::MenuInput:
			audio.PlaySound(SoundID::Input, config.soundEnabled);
			break;
		case MenuAction::MenuPress:
			menu.LoadButtons();
			break;
		case MenuAction::SwitchGameState:
			SetState(static_cast<GameState>(command.actionTarget));
			audio.PlaySound(SoundID::UISelect, config.soundEnabled);
			break;
		case MenuAction::SwitchMenuState:
			if (static_cast<MenuState>(command.actionTarget) == MenuState::Main)
				SetState(GameState::Menu);
			menu.SetState(static_cast<MenuState>(command.actionTarget), config, leaderboard);
			audio.PlaySound(SoundID::UISelect, config.soundEnabled);
			break;
		case MenuAction::StartGame:
			StartGame(menu.GetSelectedLevelConfig());
			StartDelay(GameState::GameLoop, DelayType::GameStart);
			break;
		case MenuAction::ResetGame:
			ResetGame();
			StartDelay(GameState::GameLoop, DelayType::GameStart);
			break;
		case MenuAction::ResumeGame:
			StartDelay(GameState::GameLoop, DelayType::GameStart);
			break;
		case MenuAction::PreviousMenu:
			if (menu.PreviousMenu())
				audio.PlaySound(SoundID::UISelect, config.soundEnabled);
			break;
		case MenuAction::SetScreenScale:
			config.windowResolution = static_cast<WindowResolution>(command.actionTarget);
			SaveConfig(config);
			request = {AppRequestType::SetWindowScale};
			menu.SetMenuItems(config);
			menu.PreviousMenu();
			audio.PlaySound(SoundID::UISelect, config.soundEnabled);
			break;
		case MenuAction::SetDifficulty:
			config.difficulty = static_cast<GameDifficulty>(command.actionTarget);
			SaveConfig(config);
			menu.SetMenuItems(config);
			menu.PreviousMenu();
			audio.PlaySound(SoundID::UISelect, config.soundEnabled);
			break;
		case MenuAction::ToggleSound:
			config.soundEnabled = !config.soundEnabled;
			SaveConfig(config);
			menu.SetMenuItems(config);
			menu.LoadButtons();
			audio.PlaySound(SoundID::UISelect, config.soundEnabled);
			break;
		case MenuAction::ToggleMusic:
			config.musicEnabled = !config.musicEnabled;
			SaveConfig(config);
			menu.SetMenuItems(config);
			menu.LoadButtons();
			audio.PlaySound(SoundID::UISelect, config.soundEnabled);
			break;
		case MenuAction::SavePlayerName:
			if (config.playerName != menu.GetInputString())
			{
				config.playerName = menu.GetInputString();
				SaveConfig(config);
			}
			menu.PreviousMenu();
			audio.PlaySound(SoundID::UISelect, config.soundEnabled);
			break;
		case MenuAction::ExitApplication:
			request = {AppRequestType::ExitApplication};
			break;
		default:
			break;
		}
	}

	void Game::StartDelay(const GameState &state, const DelayType &type)
	{
		SetState(GameState::Delay);
		delay.timer = 0.f;
		delay.nextGameState = state;
		delay.type = type;
		switch (type)
		{
		case DelayType::GameStart:
			delay.duration = DELAY_COUNTDOWN;
			break;
		case DelayType::GameOver:
			delay.duration = DELAY_GAME_OVER;
			break;
		default:
			break;
		}
	}

	void Game::StartDelay(const MenuState &state, const DelayType &type)
	{
		SetState(GameState::Delay);
		delay.timer = 0.f;
		delay.nextMenuState = state;
		delay.type = type;
		switch (type)
		{
		case DelayType::GameStart:
			delay.duration = DELAY_COUNTDOWN;
			break;
		case DelayType::GameOver:
			delay.duration = DELAY_GAME_OVER;
			break;
		default:
			break;
		}
	}

	void Game::UpdateDelay(const float deltaTime)
	{
		float timeLeft = delay.duration - delay.timer;

		static int wholeNumber = 0;
		switch (delay.type)
		{
		case DelayType::GameStart:
			if ((int)std::round(timeLeft) != wholeNumber)
			{
				wholeNumber = (int)std::round(timeLeft);
				if (wholeNumber == 0)
				{
					hud.SetDelayText("Go!");
					audio.PlaySound(SoundID::CountdownGo, config.soundEnabled);
				}
				else
				{
					hud.SetDelayText(std::to_string(wholeNumber));
					audio.PlaySound(SoundID::Countdown, config.soundEnabled);
				}
			}
			break;
		case DelayType::GameOver:
			hud.SetDelayText("GAME OVER!");
			break;
		default:
			break;
		}

		delay.timer += deltaTime;
		if (delay.timer >= delay.duration)
		{
			switch (delay.type)
			{
			case DelayType::GameStart:
				SetState(delay.nextGameState);
				break;
			case DelayType::GameOver:
				SetState(GameState::MenuOverlay);
				menu.SetState(delay.nextMenuState, config, leaderboard);
				break;
			default:
				break;
			}
			wholeNumber = 0;
		}
	}
}
