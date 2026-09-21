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
#include "AppRequest.h"
#include "Hud.h"
#include "MenuManager.h"
#include "AudioManager.h"

namespace SnakeGame
{
	class Game
	{
	public:
		Game();

		void Update(const float deltaTime);
		void Draw(sf::RenderTexture &texture) const;
		void HandleInput(const sf::Event &event);

		AppRequest ConsumeAppRequest();
		float GetWindowScale();

	private:
		void SetState(const GameState &gameState);
		void StartGame(const LevelConfig &levelConfig);
		void ResetGame();
		void UpdateGame(const float deltaTime);
		void SetScoreMultiplier();

		void HandleMenuCommand(const MenuCommand &command);

		void StartDelay(const GameState &state, const DelayType &type);
		void StartDelay(const MenuState &state, const DelayType &type);
		void UpdateDelay(const float deltaTime);

		Resources resources;
		Config config;
		AudioManager audio;
		MenuManager menu;

		GameState state;
		Delay delay;
		sf::Sprite background;
		Level level;
		Snake snake;
		float speed;
		int score;
		int scoreMultiplier;
		Leaderboard leaderboard;
		Hud hud;

		AppRequest request;
	};
}
