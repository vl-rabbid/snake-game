#pragma once
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Level.h"
#include "GameState.h"
#include "UI.h"
#include "Menu.h"

namespace SnakeGame
{
	struct Game
	{
		int screenWidth;
		int screenHeight;
		GameState gameState;
		Level level;
		Snake snake;
		float speed;

		std::map<MenuState, Menu> menus;
		Menu currentMenu;
		UI ui;
	};

	bool IsGameRunning(Game &game);
	void InitGame(Game &game);
	void HandleImputAndEvents(Game &game, const sf::Event &event);
	void UpdateGame(Game &game, const float deltaTime);
	void DrawGame(Game &game, sf::RenderWindow &window);
	void DeinitializeGame(Game &game, sf::RenderWindow &window);
	void SetGameState(Game &game, const GameState &gameState);
	void SetMenuState(Game &game, const MenuState &menuState);
	void StartGameLoop(Game &game);
	void UpdateGameLoop(Game &game, const float deltaTime);
	void HandleMenuImput(Game &game, const sf::Event &event);
}
