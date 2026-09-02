#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

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
    int GetRandomInt(int minValue, int maxValue);
    Position2D GetRandomPositionOnLevel(float levelWidth, float levelHeight);
}