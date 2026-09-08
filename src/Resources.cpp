#include "Resources.h"
#include <cassert>
#include <string>

namespace SnakeGame
{
    void InitResources(Resources &resources)
    {
        assert(resources.atlas.loadFromFile(std::string(RESOURCES_PATH) + "/graphics/atlas.png"));
        assert(resources.font.loadFromFile(std::string(RESOURCES_PATH) + "/fonts/monogram.ttf"));
    }

    sf::IntRect GetTextureRect(TextureID id)
    {
        switch (id)
        {
        case TextureID::SnakeBodyUp:
            return sf::IntRect(0, 0, 12, 12);
            break;
        case TextureID::SnakeBodyDown:
            return sf::IntRect(12, 0, 12, 12);
            break;
        case TextureID::SnakeBodyLeft:
            return sf::IntRect(24, 0, 12, 12);
            break;
        case TextureID::SnakeBodyRight:
            return sf::IntRect(36, 0, 12, 12);
            break;

        case TextureID::SnakeHeadUp:
            return sf::IntRect(48, 0, 12, 12);
            break;
        case TextureID::SnakeHeadDown:
            return sf::IntRect(60, 0, 12, 12);
            break;
        case TextureID::SnakeHeadLeft:
            return sf::IntRect(72, 0, 12, 12);
            break;
        case TextureID::SnakeHeadRight:
            return sf::IntRect(84, 0, 12, 12);
            break;

        case TextureID::SnakeTailUp:
            return sf::IntRect(96, 0, 12, 12);
            break;
        case TextureID::SnakeTailDown:
            return sf::IntRect(108, 0, 12, 12);
            break;
        case TextureID::SnakeTailLeft:
            return sf::IntRect(120, 0, 12, 12);
            break;
        case TextureID::SnakeTailRight:
            return sf::IntRect(132, 0, 12, 12);
            break;

        case TextureID::SnakeMouthUp:
            return sf::IntRect(0, 12, 12, 12);
            break;
        case TextureID::SnakeMouthDown:
            return sf::IntRect(12, 12, 12, 12);
            break;
        case TextureID::SnakeMouthLeft:
            return sf::IntRect(24, 12, 12, 12);
            break;
        case TextureID::SnakeMouthRight:
            return sf::IntRect(36, 12, 12, 12);
            break;

        case TextureID::SnakeCornerUpRight:
            return sf::IntRect(48, 12, 12, 12);
            break;
        case TextureID::SnakeCornerUpLeft:
            return sf::IntRect(60, 12, 12, 12);
            break;
        case TextureID::SnakeCornerDownRight:
            return sf::IntRect(72, 12, 12, 12);
            break;
        case TextureID::SnakeCornerDownLeft:
            return sf::IntRect(84, 12, 12, 12);
            break;

        case TextureID::SnakeDeadUp:
            return sf::IntRect(96, 12, 12, 12);
            break;
        case TextureID::SnakeDeadDown:
            return sf::IntRect(108, 12, 12, 12);
            break;
        case TextureID::SnakeDeadLeft:
            return sf::IntRect(120, 12, 12, 12);
            break;
        case TextureID::SnakeDeadRight:
            return sf::IntRect(132, 12, 12, 12);
            break;

        case TextureID::Apple:
            return sf::IntRect(0, 24, 12, 12);
            break;

        default:
            break;
        }
        return sf::IntRect(0, 0, 12, 12);
    }
}