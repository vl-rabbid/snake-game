#pragma once
#include "GameMath.h"
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
    enum class Direction
    {
        Right = 0,
        Up,
        Left,
        Down
    };

    struct Snake
    {
        Position2D position;
        float speed = 0.f;
        Direction direction{};
        sf::RectangleShape shape;
    };

    struct Game;

    void InitSnake(Snake &snake, const Game &game);
    void DrawSnake(Snake &snake, sf::RenderWindow &window);
    void UpdateSnake(Snake &snake, const float deltaTime);
    void HandleSnakeImput(Snake &snake, const sf::Event &event);
}