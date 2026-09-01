#include "Level.h"
#include "GameMath.h"

namespace SnakeGame
{
    void InitLevel(Level &level)
    {
        for (int x = 0; x < LEVEL_WIDTH; x++)
        {
            for (int y = 0; y < LEVEL_HEIGHT; y++)
            {
                level.cells[x][y].type = CellType::Empty;
                level.cells[x][y].shape.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                SetShapePosition(level.cells[x][y].shape, {x, y});
                UpdateCellColor(level, {x, y});
            }
        }
    }

    void DrawLevel(Level &level, sf::RenderWindow &window)
    {
        for (int x = 0; x < LEVEL_WIDTH; x++)
        {
            for (int y = 0; y < LEVEL_HEIGHT; y++)
            {
                window.draw(level.cells[x][y].shape);
            }
        }
    }

    void UpdateCellColor(Level &level, Position2D position)
    {
        switch (level.cells[position.x][position.y].type)
        {
        case CellType::Empty:
            if ((position.x + position.y) % 2 == 1)
            {
                level.cells[position.x][position.y].shape.setFillColor(COLOR_GRASS_LIGHT);
            }
            else
            {
                level.cells[position.x][position.y].shape.setFillColor(COLOR_GRASS_DARK);
            }
            break;
        case CellType::Apple:
            level.cells[position.x][position.y].shape.setFillColor(COLOR_APPLE);
            break;
        case CellType::Wall:
            level.cells[position.x][position.y].shape.setFillColor(COLOR_WALL);
            break;
        default:
            break;
        }
    }

    void SetCellType(Level &level, Position2D position, CellType cellType)
    {
        level.cells[position.x][position.y].type = cellType;
    }
}