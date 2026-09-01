#include "GameMath.h"

namespace SnakeGame
{
    void SetShapePosition(sf::RectangleShape &shape, const Position2D &position)
    {
        shape.setPosition(position.x * CELL_SIZE, position.y * CELL_SIZE);
    }
}
