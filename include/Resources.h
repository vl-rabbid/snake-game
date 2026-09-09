#pragma once
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
    enum class TextureID
    {
        SnakeBodyUp = 0,
        SnakeBodyDown,
        SnakeBodyLeft,
        SnakeBodyRight,

        SnakeHeadUp,
        SnakeHeadDown,
        SnakeHeadLeft,
        SnakeHeadRight,

        SnakeTailUp,
        SnakeTailDown,
        SnakeTailLeft,
        SnakeTailRight,

        SnakeMouthUp,
        SnakeMouthDown,
        SnakeMouthLeft,
        SnakeMouthRight,

        SnakeCornerUpRight,
        SnakeCornerUpLeft,
        SnakeCornerDownRight,
        SnakeCornerDownLeft,

        SnakeDeadUp,
        SnakeDeadDown,
        SnakeDeadLeft,
        SnakeDeadRight,

        Apple,

        UIFrame1,
        UIFrame2,
        UIFrame3
    };

    struct Resources
    {
        sf::Texture atlas;
        sf::Texture background;
        sf::Font font;

        sf::Texture button;
    };

    void InitResources(Resources &resources);
    sf::IntRect GetTextureRect(TextureID id);
    sf::Texture CreateNineSliceTexture(const sf::Texture &atlas, sf::IntRect rect, unsigned int width, unsigned int height);
}