#pragma once
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Snake.h"
#include "Level.h"
#include "StateManager.h"
#include "UI.h"
#include "Menu.h"
#include "Resources.h"
#include "Config.h"
#include "Leaderboard.h"
#include "LevelManager.h"
#include "ApplicationRequest.h"
#include "Hud.h"

namespace SnakeGame
{
	struct Game
	{
		ApplicationRequest applicationRequest;
		Config config;
		Resources resources;

		sf::Sprite background;

		GameState gameState;
		Delay delay;
		Level level;
		Snake snake;
		float speed;
		int score;
		Leaderboard leaderboard;

		std::map<MenuState, Menu> menus;
		std::vector<Menu> menuLayers;
		UI ui;
		LevelManager levelMangager;

		sf::Sound soundFX;
		sf::Sound soundJingle;

		std::string newPlayerName;

		Hud hud;
	};

	ApplicationRequest GetApplicationRequest(Game &game);
	void InitGame(Game &game);
	void HandleGameImput(Game &game, const sf::Event &event);
	void UpdateGame(Game &game, const float deltaTime);
	void DrawGame(Game &game, sf::RenderTexture &texture);
	void DeinitializeGame(Game &game);

	void SetGameState(Game &game, const GameState &gameState);

	void StartGameLoop(Game &game);
	void UpdateGameLoop(Game &game, const float deltaTime);
	int GetScoreMultiplier(GameDifficulty gameDifficulty);

	void DrawMenu(Game &game, Menu &menu, sf::RenderTexture &texture);
	void UpdateMenu(Game &game, const float deltaTime);
	void SetMenuState(Game &game, MenuState menuState);
	void HandleMenuImput(Game &game, const sf::Event &event);
	void HandleMainMenuImput(Game &game, const sf::Event &event);
	void HandleLevelSelectImput(Game &game, const sf::Event &event);
	void HandleLeaderboardImput(Game &game, const sf::Event &event);
	void HandleTypingInput(Game &game, const sf::Event &event);
	void SetInputMenuItems(Menu &menu, Game &game);
	void SetSubMenuItems(Menu &menu, Game &game, int actionTarget);
	void SetSettingsItems(Menu &menu, Game &game);

	void PlaySound(Game &game, sf::Sound &sound, const GameSound &gameSound);
	void PlayMusic(Game &game);
	void StopMusic(Game &game);
	void PauseMusic(Game &game);

	void StartGameStateDelay(Game &game, GameState nextGameState, DelayType type);
	void StartMenuStateDelay(Game &game, MenuState nextMenuState, DelayType type);
	void UpdateDelay(Game &game, const float deltaTime);

	bool IsAllowedInputChar(char32_t c);
	float GetGameWindowScale(Game &game);
}
