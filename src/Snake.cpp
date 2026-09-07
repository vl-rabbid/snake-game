#include "Snake.h"
#include "Game.h"
#include "Constants.h"

namespace SnakeGame
{
    void InitSnake(Snake &snake, Resources &resources)
    {
        snake.segments.clear();
        snake.segments.resize(INITIAL_SEGMENT_NUMBER);
        for (int i = 0; i < snake.segments.size(); i++)
        {
            snake.segments[i].position = {LEVEL_WIDTH / 2, (LEVEL_HEIGHT / 2) + i};
            snake.segments[i].direction = Direction::Up;
            snake.segments[i].sprite.setTexture(resources.atlas);
        }
        UpdateSnakeTexture(snake);
    }

    void AddSnakeSegment(Snake &snake, SnakeSegment &previous)
    {
        snake.segments.push_back(previous);
    }

    void DrawSnake(Snake &snake, sf::RenderTexture &texture)
    {
        for (int i = snake.segments.size() - 1; i >= 0; i--)
        {
            texture.draw(snake.segments[i].sprite);
        }
    }

    void UpdateSnake(Snake &snake)
    {
        UpdateHeadDirection(snake);
        for (int i = snake.segments.size() - 1; i >= 0; i--)
        {
            UpdateSegmentPosition(snake.segments[i]);
            if (i != 0)
            {
                snake.segments[i].direction = snake.segments[i - 1].direction;
            }
        }

        for (int i = 0; i < snake.segments.size(); i++)
        {
            // Loop by x
            if (snake.segments[i].position.x == LEVEL_WIDTH)
            {
                snake.segments[i].position.x -= LEVEL_WIDTH;
            }
            else if (snake.segments[i].position.x < 0)
            {
                snake.segments[i].position.x += LEVEL_WIDTH;
            }
            // Loop by y
            if (snake.segments[i].position.y == LEVEL_HEIGHT)
            {
                snake.segments[i].position.y -= LEVEL_HEIGHT;
            }
            else if (snake.segments[i].position.y < 0)
            {
                snake.segments[i].position.y += LEVEL_HEIGHT;
            }
        }
    }

    void UpdateSegmentPosition(SnakeSegment &previous)
    {
        switch (previous.direction)
        {
        case Direction::Right:
        {
            previous.position.x++;
            break;
        }
        case Direction::Up:
        {
            previous.position.y--;
            break;
        }
        case Direction::Left:
        {
            previous.position.x--;
            break;
        }
        case Direction::Down:
        {
            previous.position.y++;
            break;
        }
        }
    }

    void UpdateSnakeTexture(Snake &snake)
    {
        for (int i = snake.segments.size() - 1; i >= 0; i--)
        {
            SetSpritePosition(snake.segments[i].sprite, snake.segments[i].position);

            if (i == 0)
            {
                UpdateHeadTexture(snake.segments[i]);
            }
            else if (i == snake.segments.size() - 1)
            {
                UpdateTailTexture(snake.segments[i]);
            }
            else if (i - 1 == 0)
            {
                UpdateBodyTexture(snake.segments[i], snake.segments[i + 1]);
            }
            else
            {
                snake.segments[i].sprite.setTextureRect(snake.segments[i - 1].sprite.getTextureRect());
            }
        }
    }

    void UpdateHeadTexture(SnakeSegment &previous)
    {
        switch (previous.direction)
        {
        case Direction::Right:
        {
            previous.sprite.setTextureRect(GetTextureRect(TextureID::SnakeHeadRight));
            break;
        }
        case Direction::Up:
        {
            previous.sprite.setTextureRect(GetTextureRect(TextureID::SnakeHeadUp));
            break;
        }
        case Direction::Left:
        {
            previous.sprite.setTextureRect(GetTextureRect(TextureID::SnakeHeadLeft));
            break;
        }
        case Direction::Down:
        {
            previous.sprite.setTextureRect(GetTextureRect(TextureID::SnakeHeadDown));
            break;
        }
        }
    }

    void UpdateBodyTexture(SnakeSegment &currentSegment, SnakeSegment &previousSegment)
    {
        if (previousSegment.direction == Direction::Up && currentSegment.direction == Direction::Right || previousSegment.direction == Direction::Left && currentSegment.direction == Direction::Down)
        {
            currentSegment.sprite.setTextureRect(GetTextureRect(TextureID::SnakeCornerUpRight));
        }
        else if (previousSegment.direction == Direction::Up && currentSegment.direction == Direction::Left || previousSegment.direction == Direction::Right && currentSegment.direction == Direction::Down)
        {
            currentSegment.sprite.setTextureRect(GetTextureRect(TextureID::SnakeCornerUpLeft));
        }
        else if (previousSegment.direction == Direction::Down && currentSegment.direction == Direction::Right || previousSegment.direction == Direction::Left && currentSegment.direction == Direction::Up)
        {
            currentSegment.sprite.setTextureRect(GetTextureRect(TextureID::SnakeCornerDownRight));
        }
        else if (previousSegment.direction == Direction::Down && currentSegment.direction == Direction::Left || previousSegment.direction == Direction::Right && currentSegment.direction == Direction::Up)
        {
            currentSegment.sprite.setTextureRect(GetTextureRect(TextureID::SnakeCornerDownLeft));
        }
        else if (previousSegment.direction == Direction::Right)
        {
            currentSegment.sprite.setTextureRect(GetTextureRect(TextureID::SnakeBodyRight));
        }
        else if (previousSegment.direction == Direction::Up)
        {
            currentSegment.sprite.setTextureRect(GetTextureRect(TextureID::SnakeBodyUp));
        }
        else if (previousSegment.direction == Direction::Left)
        {
            currentSegment.sprite.setTextureRect(GetTextureRect(TextureID::SnakeBodyLeft));
        }
        else if (previousSegment.direction == Direction::Down)
        {
            currentSegment.sprite.setTextureRect(GetTextureRect(TextureID::SnakeBodyDown));
        }
    }

    void UpdateTailTexture(SnakeSegment &previous)
    {
        switch (previous.direction)
        {
        case Direction::Right:
        {
            previous.sprite.setTextureRect(GetTextureRect(TextureID::SnakeTailRight));
            break;
        }
        case Direction::Up:
        {
            previous.sprite.setTextureRect(GetTextureRect(TextureID::SnakeTailUp));
            break;
        }
        case Direction::Left:
        {
            previous.sprite.setTextureRect(GetTextureRect(TextureID::SnakeTailLeft));
            break;
        }
        case Direction::Down:
        {
            previous.sprite.setTextureRect(GetTextureRect(TextureID::SnakeTailDown));
            break;
        }
        }
    }

    void UpdateHeadDirection(Snake &snake)
    {
        while (snake.inputBuffer.size() > 0)
        {
            if (snake.inputBuffer.front() == Direction::Right || snake.inputBuffer.front() == Direction::Left)
            {
                if (snake.segments[0].direction == Direction::Up || snake.segments[0].direction == Direction::Down)
                {
                    snake.segments[0].direction = snake.inputBuffer.front();
                    snake.inputBuffer.pop_front();
                    return;
                }
            }
            else if (snake.inputBuffer.front() == Direction::Up || snake.inputBuffer.front() == Direction::Down)
            {
                if (snake.segments[0].direction == Direction::Right || snake.segments[0].direction == Direction::Left)
                {
                    snake.segments[0].direction = snake.inputBuffer.front();
                    snake.inputBuffer.pop_front();
                    return;
                }
            }
            snake.inputBuffer.pop_front();
        }
    }

    void HandleSnakeImput(Snake &snake, const sf::Event &event)
    {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
        {
            AddImputToBuffer(snake, Direction::Right);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
        {
            AddImputToBuffer(snake, Direction::Up);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
        {
            AddImputToBuffer(snake, Direction::Left);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
        {
            AddImputToBuffer(snake, Direction::Down);
        }
    }

    void AddImputToBuffer(Snake &snake, const Direction &direction)
    {
        if (snake.inputBuffer.size() < INPUT_BUFFER_SIZE)
        {
            if (snake.inputBuffer.size() == 0)
            {
                snake.inputBuffer.push_back(direction);
            }
            else if (snake.inputBuffer.back() != direction)
            {
                snake.inputBuffer.push_back(direction);
            }
        }
    }
}