#pragma once
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game/Snake.h"
#include "Game/Level.h"
#include "Game/States.h"
#include "Game/Resources.h"
#include "Game/Config.h"
#include "Game/Leaderboard.h"
#include "Game/Hud.h"
#include "Game/AudioManager.h"
#include "Menu/MenuManager.h"
#include "Application/AppRequest.h"

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
