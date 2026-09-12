#include "Level.h"

namespace SnakeGame
{
    void InitLevel(Level &level, Resources &resources)
    {
        level.apple.sprite.setTexture(resources.atlas);
        level.apple.sprite.setTextureRect(GetTextureRect(TextureID::Apple));

        level.walls.clear();
        level.walls.resize(level.config.walls.size());
        for (int i = 0; i < level.walls.size(); i++)
        {
            level.walls[i].position = level.config.walls[i];
            level.walls[i].sprite.setTexture(resources.atlas);
            level.walls[i].sprite.setTextureRect(GetRandomWallRect());
            SetSpritePosition(level.walls[i].sprite, level.walls[i].position);
        }

        level.countEmptyCells = (LEVEL_WIDTH * LEVEL_HEIGHT) - level.walls.size();
    }

    void SpawnApple(Level &level)
    {
        Position2D position;
        do
        {
            position = GetRandomPositionOnLevel(LEVEL_WIDTH, LEVEL_HEIGHT);
        } while (GetCellType(level.config, position) != CellType::Empty);

        level.apple.position = position;
        SetCellType(level.config, position, CellType::Apple);
        SetSpritePosition(level.apple.sprite, position);
    }

    void DrawLevel(Level &level, sf::RenderTexture &texture)
    {
        texture.draw(level.apple.sprite);
        for (int i = 0; i < level.walls.size(); i++)
        {
            texture.draw(level.walls[i].sprite);
        }
    }
}