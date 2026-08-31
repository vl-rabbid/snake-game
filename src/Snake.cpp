#include "Snake.h"
#include "Game.h"
#include "Constants.h"

namespace SnakeGame
{
    void InitSnake(Snake &snake, const Game &game)
    {
        snake.speed = INITIAL_SPEED;

        snake.segments.clear();
        snake.segments.resize(INITIAL_SEGMENT_NUMBER);
        for (int i = 0; i < snake.segments.size(); i++)
        {
            snake.segments[i].position = {GRID_WIDTH / 2, (GRID_HEIGHT / 2) + i};
            snake.segments[i].direction = Direction::Up;
            snake.segments[i].shape.setSize(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
            snake.segments[i].shape.setFillColor(sf::Color::Blue);
        }
    }

    void DrawSnake(Snake &snake, sf::RenderWindow &window)
    {
        for (int i = 0; i < snake.segments.size(); i++)
        {
            snake.segments[i].shape.setPosition(snake.segments[i].position.x * CELL_SIZE, snake.segments[i].position.y * CELL_SIZE);
            window.draw(snake.segments[i].shape);
        }
    }

    void UpdateSnake(Snake &snake, const float deltaTime)
    {
        static float timer = 0.f;
        float interval = 1.f / snake.speed;

        timer += deltaTime;
        if (timer >= interval)
        {
            for (int i = snake.segments.size() - 1; i >= 0; i--)
            {
                UpdateSegmentPosition(snake.segments[i]);
                if (i != 0)
                {
                    snake.segments[i].direction = snake.segments[i - 1].direction;
                }
            }
            UpdateHeadDirection(snake);
            timer -= interval;
        }
        for (int i = 0; i < snake.segments.size(); i++)
        {
            // Loop by x
            if (snake.segments[i].position.x == GRID_WIDTH)
            {
                snake.segments[i].position.x -= GRID_WIDTH;
            }
            else if (snake.segments[i].position.x < 0)
            {
                snake.segments[i].position.x += GRID_WIDTH;
            }
            // Loop by y
            if (snake.segments[i].position.y == GRID_HEIGHT)
            {
                snake.segments[i].position.y -= GRID_HEIGHT;
            }
            else if (snake.segments[i].position.y < 0)
            {
                snake.segments[i].position.y += GRID_HEIGHT;
            }
        }
    }

    void UpdateSegmentPosition(SnakeSegment &segment)
    {
        switch (segment.direction)
        {
        case Direction::Right:
        {
            segment.position.x++;
            break;
        }
        case Direction::Up:
        {
            segment.position.y--;
            break;
        }
        case Direction::Left:
        {
            segment.position.x--;
            break;
        }
        case Direction::Down:
        {
            segment.position.y++;
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