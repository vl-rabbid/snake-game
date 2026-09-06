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
                level.cells[x][y].shape.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                SetCellType(level, {x, y}, CellType::Empty);
                SetShapePosition(level.cells[x][y].shape, {x, y});
                UpdateCellColor(level, {x, y});
            }
        }
    }

    void SpawnApple(Level &level)
    {
        Position2D position;
        do
        {
            position = GetRandomPositionOnLevel(LEVEL_WIDTH, LEVEL_HEIGHT);
        } while (level.cells[position.x][position.y].type != CellType::Empty);
        level.cells[position.x][position.y].type = CellType::Apple;
        UpdateCellColor(level, position);
    }

    void DrawLevel(Level &level, sf::RenderTexture &texture)
    {
        for (int x = 0; x < LEVEL_WIDTH; x++)
        {
            for (int y = 0; y < LEVEL_HEIGHT; y++)
            {
                texture.draw(level.cells[x][y].shape);
            }
        }
    }

    void UpdateCellColor(Level &level, Position2D position)
    {
        switch (GetCellType(level, position))
        {
        case CellType::Apple:
            level.cells[position.x][position.y].shape.setFillColor(COLOR_APPLE);
            break;
        case CellType::Wall:
            level.cells[position.x][position.y].shape.setFillColor(COLOR_WALL);
            break;
        default:
            if ((position.x + position.y) % 2 == 1)
            {
                level.cells[position.x][position.y].shape.setFillColor(COLOR_GRASS_LIGHT);
            }
            else
            {
                level.cells[position.x][position.y].shape.setFillColor(COLOR_GRASS_DARK);
            }
            break;
        }
    }

    void SetCellType(Level &level, Position2D position, CellType cellType)
    {
        level.cells[position.x][position.y].type = cellType;
    }

    CellType GetCellType(Level &level, Position2D position)
    {
        return level.cells[position.x][position.y].type;
    }
}