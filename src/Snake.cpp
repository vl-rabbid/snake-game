#include "Snake.h"
#include "Game.h"
#include "Constants.h"

namespace SnakeGame
{
    void InitSnake(Snake &snake, const Game &game)
    {
        snake.position = {GRID_WIDTH / 2, GRID_HEIGHT / 2};
        snake.speed = INITIAL_SPEED;
        snake.direction = Direction::Right;

        snake.shape.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        snake.shape.setFillColor(sf::Color::Blue);
    }

    void DrawSnake(Snake &snake, sf::RenderWindow &window)
    {
        snake.shape.setPosition(snake.position.x * CELL_SIZE, snake.position.y * CELL_SIZE);
        window.draw(snake.shape);
    }

    void UpdateSnake(Snake &snake, const float deltaTime)
    {
        static float timer = 0.f;
        float interval = 1.f / snake.speed;

        timer += deltaTime;
        if (timer >= interval)
        {
            switch (snake.direction)
            {
            case Direction::Right:
            {
                snake.position.x++;
                break;
            }
            case Direction::Up:
            {
                snake.position.y--;
                break;
            }
            case Direction::Left:
            {
                snake.position.x--;
                break;
            }
            case Direction::Down:
            {
                snake.position.y++;
                break;
            }
            }
            timer -= interval;
        }

        // Loop by x
        if (snake.position.x == GRID_WIDTH)
        {
            snake.position.x -= GRID_WIDTH;
        }
        else if (snake.position.x < 0)
        {
            snake.position.x += GRID_WIDTH;
        }
        // Loop by y
        if (snake.position.y == GRID_HEIGHT)
        {
            snake.position.y -= GRID_HEIGHT;
        }
        else if (snake.position.y < 0)
        {
            snake.position.y += GRID_HEIGHT;
        }
    }

    void HandleSnakeImput(Snake &snake, const sf::Event &event)
    {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
        {
            snake.direction = Direction::Right;
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
        {
            snake.direction = Direction::Up;
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
        {
            snake.direction = Direction::Left;
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
        {
            snake.direction = Direction::Down;
        }
    }
}