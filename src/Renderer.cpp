#include "Renderer.h"
#include <cmath>

namespace SnakeGame
{
    void InitRenderer(Renderer &renderer, float gameWidth, float gameHeight)
    {

        renderer.window.create(sf::VideoMode(gameWidth, gameHeight), "Snake game!");
        renderer.window.setFramerateLimit(60);

        renderer.gameTexture.create(gameWidth, gameHeight);
        renderer.gameTexture.setSmooth(false);

        renderer.gameSprite.setTexture(renderer.gameTexture.getTexture());
        renderer.gameSprite.setTextureRect(sf::IntRect(0, 0, gameWidth, gameHeight));
    }

    void SetRendererScale(Renderer &renderer, float screenScale)
    {
        sf::Vector2u gameSize = renderer.gameTexture.getSize();
        renderer.window.create(sf::VideoMode(gameSize.x * screenScale, gameSize.y * screenScale), "Snake game!");
        renderer.gameSprite.setScale(screenScale, screenScale);
    }
}
