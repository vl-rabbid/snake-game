#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"

int main()
{
	using namespace SnakeGame;

	Game game;
	InitGame(game);

	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	while (IsGameRunning(game))
	{
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		sf::Event event;
		while (game.renderer.window.pollEvent(event))
		{
			HandleImputAndEvents(game, event);
		}

		UpdateGame(game, deltaTime);

		game.renderer.gameTexture.clear(COLOR_BASE);
		DrawGame(game, game.renderer.gameTexture);
		game.renderer.gameTexture.display();

		game.renderer.window.clear();
		game.renderer.window.draw(game.renderer.gameSprite);
		game.renderer.window.display();
	}
	DeinitializeGame(game, game.renderer.window);

	return 0;
}
