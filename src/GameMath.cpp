#include "GameMath.h"

namespace SnakeGame
{
    void SetShapePosition(sf::RectangleShape &shape, const Position2D &position)
    {
        shape.setPosition(position.x * CELL_SIZE, position.y * CELL_SIZE);
    }

    int GetRandomInt(int minValue, int maxValue)
    {
        return minValue + rand() % (maxValue - minValue + 1);
    }

    Position2D GetRandomPositionOnLevel(float levelWidth, float levelHeight)
    {
        Position2D result;
        result.x = GetRandomInt(0, levelWidth - 1);
        result.y = GetRandomInt(0, levelHeight - 1);
        return result;
    }
}
