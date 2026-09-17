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

    class Snake
    {
    public:
        Snake() = default;

        void Reset(const Resources &resources, const Position2D &spawn, int length, int maxLength);
        void UpdatePosition();
        void UpdateSprites(bool isDead, bool isMouthOpen);
        void Draw(sf::RenderTexture &texture) const;
        void HandleInput(const sf::Event &event);
        void Grow(const Resources &resources);
        Position2D GetHeadPosition() const;
        Position2D GetTailPosition() const;
        unsigned int GetLength() const;

    private:
        void UpdateHeadDirection();
        void MoveSegments();
        void WrapSegments();
        void SetHeadTexture(bool isDead, bool isMouthOpen);
        void SetBodyTexture(SnakeSegment &segment, const SnakeSegment &nextSegment);
        void SetTailTexture();
        void AddInputToBuffer(const Direction &direction);

        std::vector<SnakeSegment> segments;
        std::deque<Direction> inputBuffer;
        Position2D lastTailPosition;
        Direction lastTailDirection;
    };
}