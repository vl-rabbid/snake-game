#include "Level.h"
#include "GameMath.h"
#include "Resources.h"
#include <fstream>
#include <filesystem>

namespace SnakeGame
{
    void InitLevel(Level &level, Resources &resources)
    {
        LoadLevel(level.config, std::string(RESOURCES_PATH) + "/levels/level1.lvl");

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
        level.walls.resize(level.config.walls.size());
        for (int i = 0; i < level.walls.size(); i++)
        {
            level.walls[i].position = level.config.walls[i];
            level.walls[i].sprite.setTexture(resources.atlas);
            level.walls[i].sprite.setTextureRect(GetRandomWallRect());
            SetSpritePosition(level.walls[i].sprite, level.walls[i].position);
            level.cells[level.walls[i].position.x][level.walls[i].position.y] = CellType::Wall;
        }

        level.countEmptyCells = (LEVEL_WIDTH * LEVEL_HEIGHT) - level.walls.size();
    }

    void SpawnApple(Level &level)
    {
        Position2D position;
        do
        {
            position = GetRandomPositionOnLevel(LEVEL_WIDTH, LEVEL_HEIGHT);
        } while (level.cells[position.x][position.y] != CellType::Empty);

        level.apple.position = position;
        level.cells[position.x][position.y] = CellType::Apple;
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
        level.cells[position.x][position.y] = cellType;
    }

    CellType GetCellType(Level &level, Position2D position)
    {
        return level.cells[position.x][position.y];
    }

    void LoadLevel(LevelConfig &levelConfig, std::string filePath)
    {
        SetEmptyLevel(levelConfig);

        std::filesystem::path path = filePath;
        levelConfig.id = path.stem().string();
        std::ifstream file(filePath);
        if (file.is_open())
        {
            std::string line;
            while (std::getline(file, line))
            {
                int pos = line.find('=');
                if (pos == std::string::npos)
                    continue;

                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);

                if (key == "name")
                    levelConfig.name = value;
                else if (key == "snakeSpawn")
                    levelConfig.snakeSpawn = ParsePosition(value);
                else if (key == "snakeSize")
                    levelConfig.snakeSize = std::stoi(value);
                else if (key == "wallCount")
                    levelConfig.walls.resize(std::stoi(value));
                else if (key == "wall")
                {
                    levelConfig.walls.push_back(ParsePosition(value));
                }
            }
            file.close();
        }
    }

    void SetEmptyLevel(LevelConfig &levelConfig)
    {
        levelConfig.id = "empty";
        levelConfig.name = "level";
        levelConfig.snakeSpawn = {LEVEL_WIDTH / 2, (LEVEL_HEIGHT / 2)};
        levelConfig.snakeSize = 3;
        levelConfig.walls.clear();
    }
}