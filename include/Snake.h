#pragma once
#include "GameMath.h"
#include <SFML/Graphics.hpp>
#include <deque>

namespace SnakeGame
{
    enum class Direction
    {
        Right = 0,
        Up,
        Left,
        Down
    };

    struct SnakeSegment
    {
        Position2D position;
        sf::RectangleShape shape;
        Direction direction{};
    };

    struct Snake
    {
        std::vector<SnakeSegment> segments;
        float speed = 0.f;
        std::deque<Direction> inputBuffer;
    };

    struct Game;

    void InitSnake(Snake &snake, const Game &game);
    void DrawSnake(Snake &snake, sf::RenderWindow &window);
    void UpdateSnake(Snake &snake, const float deltaTime);
    void UpdateSegmentPosition(SnakeSegment &segment);
    void UpdateHeadDirection(Snake &snake);
    void HandleSnakeImput(Snake &snake, const sf::Event &event);
    void AddImputToBuffer(Snake &snake, const Direction &direction);
}