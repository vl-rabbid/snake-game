#pragma once
#include <SFML/Graphics.hpp>
#include "Game/Constants.h"

namespace SnakeGame
{
    struct Position2D
    {
        int x = 0;
        int y = 0;

        bool operator==(const Position2D other) const
        {
            return x == other.x && y == other.y;
        }
    };

    void SetShapePosition(sf::RectangleShape &shape, const Position2D &position);
    void SetSpritePosition(sf::Sprite &sprite, const Position2D &position);
    void CenterTextOnSprite(sf::Text &text, const sf::Sprite &sprite);
    int GetRandomInt(int minValue, int maxValue);
    Position2D GetRandomPositionOnLevel(int levelWidth, int levelHeight);
    void SetTextRelativeOrigin(sf::Text &text, float originX, float originY);
    void SetTextRelativePosition(sf::Text &text, float relativePositionX, float relativePositionY);
    int CellsBetween(const Position2D &firstPosition, const Position2D &secondPosition);
    Position2D ParsePosition(const std::string &value);

}