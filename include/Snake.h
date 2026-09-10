#pragma once
#include "GameMath.h"
#include <SFML/Graphics.hpp>
#include <deque>
#include "Resources.h"

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
        Direction direction{};
        sf::Sprite sprite;
    };

    struct Snake
    {
        std::vector<SnakeSegment> segments;
        std::deque<Direction> inputBuffer;
    };

    struct Game;

    void InitSnake(Snake &snake, Resources &resources, Position2D &spawn, int snakeSize, int maxLength);
    void AddSnakeSegment(Snake &snake, SnakeSegment &segment);
    void DrawSnake(Snake &snake, sf::RenderTexture &texture);
    void UpdateSnake(Snake &snake);
    void UpdateSegmentPosition(SnakeSegment &segment);
    void UpdateSnakeTexture(Snake &snake, bool isDead, bool isMouthOpen);
    void UpdateHeadTexture(SnakeSegment &segment, bool isDead, bool isMouthOpen);
    void UpdateBodyTexture(SnakeSegment &segment, SnakeSegment &head);
    void UpdateTailTexture(SnakeSegment &segment);
    void UpdateHeadDirection(Snake &snake);
    void HandleSnakeImput(Snake &snake, const sf::Event &event);
    void AddImputToBuffer(Snake &snake, const Direction &direction);
}