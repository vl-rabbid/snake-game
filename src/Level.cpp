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

        level.walls.clear();
        level.walls.resize(LEVEL_WIDTH);
        for (int i = 0; i < level.walls.size(); i++)
        {
            level.walls[i].position = {i, LEVEL_HEIGHT - 1};
            level.walls[i].sprite.setTexture(resources.atlas);
            level.walls[i].sprite.setTextureRect(GetRandomWallRect());
            SetSpritePosition(level.walls[i].sprite, level.walls[i].position);
            level.cells[level.walls[i].position.x][level.walls[i].position.y].type = CellType::Wall;
        }

        level.countEmptyCells = (LEVEL_WIDTH * LEVEL_HEIGHT) - level.walls.size();
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
        for (int i = 0; i < level.walls.size(); i++)
        {
            texture.draw(level.walls[i].sprite);
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