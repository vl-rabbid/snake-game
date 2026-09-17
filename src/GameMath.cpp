#include "GameMath.h"
#include <cmath>

namespace SnakeGame
{
    void SetShapePosition(sf::RectangleShape &shape, const Position2D &position)
    {
        shape.setPosition(position.x * CELL_SIZE, (position.y + HUD_HEIGHT) * CELL_SIZE);
    }

    void SetSpritePosition(sf::Sprite &sprite, const Position2D &position)
    {
        sprite.setPosition(position.x * CELL_SIZE, (position.y + HUD_HEIGHT) * CELL_SIZE);
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
        sf::Vector2f origin = {std::round(spriteRect.width * originX), std::round(spriteRect.height * originY)};
        text.setOrigin(origin);
    }

    void SetTextRelativePosition(sf::Text &text, float relativePositionX, float relativePositionY)
    {
        sf::Vector2f position = {std::round(LEVEL_WIDTH * CELL_SIZE * relativePositionX), std::round((LEVEL_HEIGHT + HUD_HEIGHT) * CELL_SIZE * relativePositionY)};
        text.setPosition(position);
    }

    int CellsBetween(const Position2D &firstPosition, const Position2D &secondPosition)
    {
        int dx = std::abs(secondPosition.x - firstPosition.x);
        int dy = std::abs(secondPosition.y - firstPosition.y);
        return std::max(dx, dy);
    }

    Position2D ParsePosition(const std::string &value)
    {
        Position2D position;

        int comma = value.find(',');
        position.x = std::stoi(value.substr(0, comma));
        position.y = std::stoi(value.substr(comma + 1));
        return position;
    }
}
