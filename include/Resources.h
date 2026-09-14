#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameMath.h"

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

        SliderHorizontal,

        Up,
        Down,

        UIFrame4,
        UIFrame5,

        Left,
        Right,

        SliderVertical,

        UIFrame6
    };

    struct GameSound
    {
        sf::SoundBuffer buffer;
        float volume = 100.f;
        std::string path;
    };

    struct Resources
    {
        sf::Texture atlas;
        sf::Texture background;
        sf::Font font;

        sf::Texture buttonEnabled;
        sf::Texture buttonDisabled;
        sf::Texture buttonPressed;
        sf::Texture subMenu;
        sf::Texture subMenuTitle;

        sf::Texture hud;
        sf::Texture hudLevelName;
        sf::Texture hudScore;

        sf::Texture levelSelectButton;
        sf::Texture levelPreviewFrame;

        sf::Texture leaderboardFrame;
        sf::Texture leaderboardLabelFrame;

        sf::Texture inputMenu;
        sf::Texture inputField;

        GameSound uiMoveVertical;
        GameSound uiMoveHorizontal;
        GameSound uiSelect;
        GameSound appleEaten;
        GameSound wall;
        GameSound gameOver;
        GameSound countdown;
        GameSound countdownGo;
        GameSound input;

        sf::Music music;
    };

    void InitResources(Resources &resources);
    sf::IntRect GetTextureRect(TextureID id);
    sf::IntRect GetRandomWallRect();
    sf::Texture CreateNineSliceTexture(const sf::Texture &atlas, sf::IntRect rect, unsigned int width, unsigned int height);
}