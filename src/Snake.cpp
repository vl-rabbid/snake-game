#include "Snake.h"

namespace SnakeGame
{
    void Snake::Reset(const Resources &resources, const Position2D &spawn, int length, int maxLength)
    {
        segments.clear();
        segments.reserve(maxLength);
        for (int i = 0; i < length; i++)
        {
            SnakeSegment segment;
            segment.position = {spawn.x, spawn.y + i};
            segment.direction = Direction::Up;
            SetSpriteAtlas(resources, segment.sprite, TextureID::SnakeBodyUp);
            segments.push_back(segment);
        }
        UpdateSprites(false, false);
    }

    void Snake::UpdatePosition()
    {
        lastTailPosition = segments.back().position;
        lastTailDirection = segments.back().direction;

        UpdateHeadDirection();
        MoveSegments();
        WrapSegments();
    }

    void Snake::UpdateSprites(bool isDead, bool isMouthOpen)
    {
        for (int i = segments.size() - 1; i >= 0; i--)
        {
            SetSpritePosition(segments[i].sprite, segments[i].position);
            if (i == 0)
                SetHeadTexture(isDead, isMouthOpen);
            else if (i == segments.size() - 1)
                SetTailTexture();
            else if (i - 1 == 0)
                SetBodyTexture(segments[i], segments[i + 1]);
            else
                segments[i].sprite.setTextureRect(segments[i - 1].sprite.getTextureRect());
        }
    }

    void Snake::Draw(sf::RenderTexture &texture) const
    {
        for (int i = segments.size() - 1; i >= 0; i--)
        {
            texture.draw(segments[i].sprite);
        }
    }

    void Snake::HandleInput(const sf::Event &event)
    {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
            AddInputToBuffer(Direction::Right);
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
            AddInputToBuffer(Direction::Up);
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
            AddInputToBuffer(Direction::Left);
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
            AddInputToBuffer(Direction::Down);
    }

    void Snake::Grow(const Resources &resources)
    {
        SnakeSegment segment;
        segment.position = lastTailPosition;
        segment.direction = lastTailDirection;
        SetSpriteAtlas(resources, segment.sprite, TextureID::SnakeBodyUp);
        segments.push_back(segment);
    }

    Position2D Snake::GetHeadPosition() const
    {
        return segments.front().position;
    }

    Position2D Snake::GetTailPosition() const
    {
        return segments.back().position;
    }

    unsigned int Snake::GetLength() const
    {
        return segments.size();
    }

    void Snake::UpdateHeadDirection()
    {
        while (inputBuffer.size() > 0)
        {
            if (inputBuffer.front() == Direction::Right || inputBuffer.front() == Direction::Left)
            {
                if (segments[0].direction == Direction::Up || segments[0].direction == Direction::Down)
                {
                    segments[0].direction = inputBuffer.front();
                    inputBuffer.pop_front();
                    return;
                }
            }
            else if (inputBuffer.front() == Direction::Up || inputBuffer.front() == Direction::Down)
            {
                if (segments[0].direction == Direction::Right || segments[0].direction == Direction::Left)
                {
                    segments[0].direction = inputBuffer.front();
                    inputBuffer.pop_front();
                    return;
                }
            }
            inputBuffer.pop_front();
        }
    }

    void Snake::MoveSegments()
    {
        for (int i = segments.size() - 1; i >= 0; i--)
        {
            switch (segments[i].direction)
            {
            case Direction::Right:
            {
                segments[i].position.x++;
                break;
            }
            case Direction::Up:
            {
                segments[i].position.y--;
                break;
            }
            case Direction::Left:
            {
                segments[i].position.x--;
                break;
            }
            case Direction::Down:
            {
                segments[i].position.y++;
                break;
            }
            }

            if (i != 0)
            {
                segments[i].direction = segments[i - 1].direction;
            }
        }
    }

    void Snake::WrapSegments()
    {
        for (auto &segment : segments)
        {
            if (segment.position.x == LEVEL_WIDTH)
                segment.position.x -= LEVEL_WIDTH;
            else if (segment.position.x < 0)
                segment.position.x += LEVEL_WIDTH;

            if (segment.position.y == LEVEL_HEIGHT)
                segment.position.y -= LEVEL_HEIGHT;
            else if (segment.position.y < 0)
                segment.position.y += LEVEL_HEIGHT;
        }
    }

    void Snake::SetHeadTexture(bool isDead, bool isMouthOpen)
    {
        SnakeSegment &head = segments.front();
        switch (head.direction)
        {
        case Direction::Right:
        {
            if (isDead)
                UpdateSpriteAtlas(head.sprite, TextureID::SnakeDeadRight);
            else if (isMouthOpen)
                UpdateSpriteAtlas(head.sprite, TextureID::SnakeMouthRight);
            else
                UpdateSpriteAtlas(head.sprite, TextureID::SnakeHeadRight);
            break;
        }
        case Direction::Up:
        {
            if (isDead)
                UpdateSpriteAtlas(head.sprite, TextureID::SnakeDeadUp);
            else if (isMouthOpen)
                UpdateSpriteAtlas(head.sprite, TextureID::SnakeMouthUp);
            else
                UpdateSpriteAtlas(head.sprite, TextureID::SnakeHeadUp);
            break;
        }
        case Direction::Left:
        {
            if (isDead)
                UpdateSpriteAtlas(head.sprite, TextureID::SnakeDeadLeft);
            else if (isMouthOpen)
                UpdateSpriteAtlas(head.sprite, TextureID::SnakeMouthLeft);
            else
                UpdateSpriteAtlas(head.sprite, TextureID::SnakeHeadLeft);
            break;
        }
        case Direction::Down:
        {
            if (isDead)
                UpdateSpriteAtlas(head.sprite, TextureID::SnakeDeadDown);
            else if (isMouthOpen)
                UpdateSpriteAtlas(head.sprite, TextureID::SnakeMouthDown);
            else
                UpdateSpriteAtlas(head.sprite, TextureID::SnakeHeadDown);
            break;
        }
        }
    }

    void Snake::SetBodyTexture(SnakeSegment &segment, const SnakeSegment &nextSegment)
    {
        if (nextSegment.direction == Direction::Up && segment.direction == Direction::Right || nextSegment.direction == Direction::Left && segment.direction == Direction::Down)
            UpdateSpriteAtlas(segment.sprite, TextureID::SnakeCornerUpRight);
        else if (nextSegment.direction == Direction::Up && segment.direction == Direction::Left || nextSegment.direction == Direction::Right && segment.direction == Direction::Down)
            UpdateSpriteAtlas(segment.sprite, TextureID::SnakeCornerUpLeft);
        else if (nextSegment.direction == Direction::Down && segment.direction == Direction::Right || nextSegment.direction == Direction::Left && segment.direction == Direction::Up)
            UpdateSpriteAtlas(segment.sprite, TextureID::SnakeCornerDownRight);
        else if (nextSegment.direction == Direction::Down && segment.direction == Direction::Left || nextSegment.direction == Direction::Right && segment.direction == Direction::Up)
            UpdateSpriteAtlas(segment.sprite, TextureID::SnakeCornerDownLeft);
        else if (nextSegment.direction == Direction::Right)
            UpdateSpriteAtlas(segment.sprite, TextureID::SnakeBodyRight);
        else if (nextSegment.direction == Direction::Up)
            UpdateSpriteAtlas(segment.sprite, TextureID::SnakeBodyUp);
        else if (nextSegment.direction == Direction::Left)
            UpdateSpriteAtlas(segment.sprite, TextureID::SnakeBodyLeft);
        else if (nextSegment.direction == Direction::Down)
            UpdateSpriteAtlas(segment.sprite, TextureID::SnakeBodyDown);
    }

    void Snake::SetTailTexture()
    {
        SnakeSegment &tail = segments.back();
        switch (tail.direction)
        {
        case Direction::Right:
        {
            UpdateSpriteAtlas(tail.sprite, TextureID::SnakeTailRight);
            break;
        }
        case Direction::Up:
        {
            UpdateSpriteAtlas(tail.sprite, TextureID::SnakeTailUp);
            break;
        }
        case Direction::Left:
        {
            UpdateSpriteAtlas(tail.sprite, TextureID::SnakeTailLeft);
            break;
        }
        case Direction::Down:
        {
            UpdateSpriteAtlas(tail.sprite, TextureID::SnakeTailDown);
            break;
        }
        }
    }

    void Snake::AddInputToBuffer(const Direction &direction)
    {
        if (inputBuffer.size() < INPUT_BUFFER_SIZE)
        {
            if (inputBuffer.size() == 0)
                inputBuffer.push_back(direction);
            else if (inputBuffer.back() != direction)
                inputBuffer.push_back(direction);
        }
    }
}