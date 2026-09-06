#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"

int main()
{
	using namespace SnakeGame;

	Game game;
	InitGame(game);

	sf::RenderWindow window(sf::VideoMode(game.gameWidth * game.screenScale, game.gameHeight * game.screenScale), "Snake game!");
	window.setFramerateLimit(60);
	sf::RenderTexture gameTexture;
	gameTexture.create(game.gameWidth, game.gameHeight);
	gameTexture.setSmooth(false);
	sf::Sprite gameSprite;
	gameSprite.setTexture(gameTexture.getTexture());
	gameSprite.setTextureRect(sf::IntRect(0, 0, game.gameWidth, game.gameHeight));
	gameSprite.setScale(game.screenScale, game.screenScale);

	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	while (IsGameRunning(game))
	{
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		sf::Event event;
		while (window.pollEvent(event))
		{
			HandleImputAndEvents(game, event);
		}

		UpdateGame(game, deltaTime);

		gameTexture.clear();
		DrawGame(game, gameTexture);
		gameTexture.display();

		window.clear();
		window.draw(gameSprite);
		window.display();
	}
	DeinitializeGame(game, window);

	return 0;
}
