#include "Level.h"
#include "GameMath.h"
#include "Resources.h"

namespace SnakeGame
{
    void InitLevel(Level &level, Resources &resources)
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
        level.apple.sprite.setTexture(resources.atlas);
        level.apple.sprite.setTextureRect(GetTextureRect(TextureID::Apple));
    }

    void SpawnApple(Level &level)
    {
        Position2D position;
        do
        {
            position = GetRandomPositionOnLevel(LEVEL_WIDTH, LEVEL_HEIGHT);
        } while (level.cells[position.x][position.y].type != CellType::Empty);

        level.apple.position = position;
        level.cells[position.x][position.y].type = CellType::Apple;
        SetSpritePosition(level.apple.sprite, position);
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
        texture.draw(level.apple.sprite);
    }

    void UpdateCellColor(Level &level, Position2D position)
    {
        switch (GetCellType(level, position))
        {
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