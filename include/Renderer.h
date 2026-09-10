#pragma once
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
    enum class ScreenResolution
    {
        R720x540 = 3,
        R960x720 = 4,
        R1200x900 = 5,
        R1440x1080 = 6
    };

    struct Renderer
    {
        sf::RenderWindow window;
        sf::RenderTexture gameTexture;
        sf::Sprite gameSprite;
    };

    void InitRenderer(Renderer &renderer, float gameWidth, float gameHeight);
    void SetRendererScale(Renderer &renderer, float screenScale);
}
