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

        Wall1,
        Wall2,
        Wall3,
        Wall4,
        Wall5,
        Wall6,
        Wall7,
        Wall8,

        UIFrame1,
        UIFrame2,
        UIFrame3,

        SelectorTopLeft,
        SelectorTopRight,
        SelectorBottomLeft,
        SelectorBottomRight,

        Slider,

        MenuUp,
        MenuDown
    };

    struct Resources
    {
        sf::Texture atlas;
        sf::Texture background;
        sf::Font font;

        sf::Texture button;
        sf::Texture subMenu;
        sf::Texture subMenuTitle;
    };

    void InitResources(Resources &resources);
    sf::IntRect GetTextureRect(TextureID id);
    sf::IntRect GetRandomWallRect();
    sf::Texture CreateNineSliceTexture(const sf::Texture &atlas, sf::IntRect rect, unsigned int width, unsigned int height);
}