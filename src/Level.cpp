#include "Level.h"
#include "GameMath.h"
#include "Resources.h"

namespace SnakeGame
{
    void InitLevel(Level &level, Resources &resources)
    {
        level.background.setTexture(resources.background);
        for (int x = 0; x < LEVEL_WIDTH; x++)
        {
            for (int y = 0; y < LEVEL_HEIGHT; y++)
            {
                SetCellType(level, {x, y}, CellType::Empty);
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
    }

    void DrawLevel(Level &level, sf::RenderTexture &texture)
    {
        texture.draw(level.background);
        texture.draw(level.apple.sprite);
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