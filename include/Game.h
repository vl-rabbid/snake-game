#pragma once
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Level.h"
#include "GameState.h"
#include "UI.h"
#include "Menu.h"
#include "Resources.h"
#include "Renderer.h"
#include "Config.h"
#include "Leaderboard.h"

namespace SnakeGame
{
	struct Game
	{
		Config config;
		Renderer renderer;
		Resources resources;

		GameState gameState;
		Level level;
		Snake snake;
		float speed;
		int score;
		Leaderboard leaderboard;

		std::map<MenuState, Menu> menus;
		std::vector<Menu> menuLayers;
		UI ui;
	};

	bool IsGameRunning(Game &game);
	void InitGame(Game &game);
	void HandleImputAndEvents(Game &game, const sf::Event &event);
	void UpdateGame(Game &game, const float deltaTime);
	void DrawGame(Game &game, sf::RenderTexture &texture);
	void DeinitializeGame(Game &game, sf::RenderWindow &window);
	void SetGameState(Game &game, const GameState &gameState);
	void SetMenuState(Game &game, MenuState menuState);
	void UpdateMenuLayer(Game &game);
	void StartGameLoop(Game &game);
	void UpdateGameLoop(Game &game, const float deltaTime);
	void HandleMenuImput(Game &game, const sf::Event &event);
	int GetScoreMultiplier(GameDifficulty gameDifficulty);
}
