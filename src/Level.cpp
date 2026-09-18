#include "Level.h"

namespace SnakeGame
{
    void Level::Init(const LevelConfig &config, const Resources &resources)
    {
        SetSpriteAtlas(resources, apple.sprite, TextureID::Apple);

        id = config.GetId();
        name = config.GetName();
        snakeSpawn = config.GetSnakeSpawn();
        snakeSize = config.GetSnakeSize();

        const std::vector<Position2D> &configWalls = config.GetWalls();
        walls.clear();
        walls.resize(configWalls.size());
        for (int i = 0; i < walls.size(); i++)
        {
            walls[i].position = configWalls[i];
            walls[i].sprite.setTexture(resources.atlas);
            walls[i].sprite.setTextureRect(GetRandomWallRect());
            SetSpritePosition(walls[i].sprite, walls[i].position);
        }
        maxSnakeLength = (LEVEL_WIDTH * LEVEL_HEIGHT) - walls.size();
    }

    void Level::ResetState()
    {
        state.SetEmpty();
        for (auto &wall : walls)
            state.SetCellType(wall.position, CellType::Wall);
        Position2D snakePosition = snakeSpawn;
        for (int i = 0; i < snakeSize; i++)
        {
            state.SetCellType(snakePosition, CellType::Snake);
            snakePosition.y += 1;
        }
    }

    void Level::SpawnApple()
    {
        Position2D position;
        do
        {
            position = GetRandomPositionOnLevel(LEVEL_WIDTH, LEVEL_HEIGHT);
        } while (state.GetCellType(position) != CellType::Empty);

        apple.position = position;
        state.SetCellType(position, CellType::Apple);
        SetSpritePosition(apple.sprite, position);
    }

    void Level::Draw(sf::RenderTexture &texture) const
    {
        texture.draw(apple.sprite);
        for (auto &wall : walls)
            texture.draw(wall.sprite);
    }

    void Level::SetState(const Position2D &position, const CellType &type)
    {
        state.SetCellType(position, type);
    }

    CellType Level::GetState(const Position2D &position) const
    {
        return state.GetCellType(position);
    }

    Position2D Level::GetApplePosition() const
    {
        return apple.position;
    }

    const std::string &Level::GetId() const
    {
        return id;
    }

    const std::string &Level::GetName() const
    {
        return name;
    }

    Position2D Level::GetSnakeSpawn() const
    {
        return snakeSpawn;
    }

    int Level::GetSnakeSize() const
    {
        return snakeSize;
    }

    int Level::GetMaxSnakeLength() const
    {
        return maxSnakeLength;
    }

}