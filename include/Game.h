#pragma once
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Snake.h"
#include "Level.h"
#include "StateManager.h"
#include "Resources.h"
#include "Config.h"
#include "Leaderboard.h"
#include "ApplicationRequest.h"
#include "Hud.h"
#include "MenuManager.h"
#include "AudioManager.h"

namespace SnakeGame
{
	struct Game
	{
		ApplicationRequest applicationRequest;
		Config config;
		Resources resources;
		AudioManager audio;

		MenuManager menu;

		sf::Sprite background;
		GameState gameState;
		Delay delay;
		Level level;
		Snake snake;
		float speed;
		int score;
		Leaderboard leaderboard;
		Hud hud;
	};

	ApplicationRequest GetApplicationRequest(Game &game);
	void InitGame(Game &game);
	void HandleGameImput(Game &game, const sf::Event &event);
	void UpdateGame(Game &game, const float deltaTime);
	void DrawGame(Game &game, sf::RenderTexture &texture);

	void SetGameState(Game &game, const GameState &gameState);

	void StartGameLoop(Game &game, const LevelConfig &levelConfig);
	void ResetGameLoop(Game &game);
	void UpdateGameLoop(Game &game, const float deltaTime);
	int GetScoreMultiplier(GameDifficulty gameDifficulty);

	void StartGameStateDelay(Game &game, GameState nextGameState, DelayType type);
	void StartMenuStateDelay(Game &game, MenuState nextMenuState, DelayType type);
	void UpdateDelay(Game &game, const float deltaTime);

	float GetGameWindowScale(Game &game);

	void HandleMenuCommand(Game &game, MenuCommand &command);
}
