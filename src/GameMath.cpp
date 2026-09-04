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

    Position2D GetRandomPositionOnLevel(int levelWidth, int levelHeight)
    {
        Position2D result;
        result.x = GetRandomInt(0, levelWidth - 1);
        result.y = GetRandomInt(0, levelHeight - 1);
        return result;
    }

    void SetTextRelativeOrigin(sf::Text &text, float originX, float originY)
    {
        sf::FloatRect spriteRect = text.getLocalBounds();
        sf::Vector2f origin = {spriteRect.width * originX, spriteRect.height * originY};
        text.setOrigin(origin);
    }

    void SetTextRelativePosition(sf::Text &text, int levelWidth, int levelHeight, float relativePositionX, float relativePositionY)
    {
        sf::Vector2f position = {levelWidth * CELL_SIZE * relativePositionX, levelHeight * CELL_SIZE * relativePositionY};
        text.setPosition(position);
    }

    void ShiftTextPozition(sf::Text &text, float shiftX, float shiftY)
    {
        sf::Vector2f position = text.getPosition();
        position.x += shiftX;
        position.y += shiftY;
        text.setPosition(position);
    }
}
