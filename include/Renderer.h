#pragma once
#include <SFML/Graphics.hpp>
#include "Config.h"

namespace SnakeGame
{
    struct Renderer
    {
        sf::RenderWindow window;
        sf::RenderTexture gameTexture;
        sf::Sprite gameSprite;
    };

    void InitRenderer(Renderer &renderer, float gameWidth, float gameHeight);
    void SetRendererResolution(Renderer &renderer, WindowResolution windowResolution);
}
