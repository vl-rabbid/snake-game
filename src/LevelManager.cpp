#include "LevelManager.h"
#include <fstream>
#include <filesystem>

namespace SnakeGame
{
    void LoadLevelManager(LevelManager &levelMangager)
    {
        levelMangager.firstDisplayedItem = 0;
        levelMangager.selected = 0;
        levelMangager.levels.clear();

        const std::filesystem::path levelsPath = std::filesystem::path(RESOURCES_PATH) / "levels";

        if (std::filesystem::exists(levelsPath) && std::filesystem::is_directory(levelsPath))
        {
            for (const auto &entry : std::filesystem::directory_iterator(levelsPath))
            {
                if (entry.is_regular_file() && entry.path().extension() == ".lvl")
                {
                    levelMangager.levels.emplace_back();
                    LoadLevel(levelMangager.levels.back(), entry.path().string());
                }
            }
        }

        if (levelMangager.levels.size() == 0)
        {
            levelMangager.levels.emplace_back();
            SetEmptyLevel(levelMangager.levels.back());
            UpdateCellTypes(levelMangager.levels.back());
        }
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
                    levelConfig.walls.reserve(std::stoi(value));
                else if (key == "wall")
                    levelConfig.walls.push_back(ParsePosition(value));
            }
            file.close();
        }
        UpdateCellTypes(levelConfig);
    }

    void UpdateCellTypes(LevelConfig &levelConfig)
    {
        for (int i = 0; i < levelConfig.walls.size(); i++)
        {
            SetCellType(levelConfig, levelConfig.walls[i], CellType::Wall);
        }

        Position2D snakePosition = levelConfig.snakeSpawn;
        for (int i = 0; i < levelConfig.snakeSize; i++)
        {
            SetCellType(levelConfig, snakePosition, CellType::Snake);
            snakePosition.y += 1;
        }
    }

    void SetEmptyLevel(LevelConfig &levelConfig)
    {
        levelConfig.id = "empty";
        levelConfig.name = "Empty";
        levelConfig.snakeSpawn = {LEVEL_WIDTH / 2, (LEVEL_HEIGHT / 2)};
        levelConfig.snakeSize = 3;
        levelConfig.walls.clear();

        for (int x = 0; x < LEVEL_WIDTH; x++)
        {
            for (int y = 0; y < LEVEL_HEIGHT; y++)
            {
                SetCellType(levelConfig, {x, y}, CellType::Empty);
            }
        }
    }

    sf::VertexArray GenerateLevelPreview(const LevelConfig &level)
    {
        sf::VertexArray vertices(
            sf::Quads,
            LEVEL_WIDTH * LEVEL_HEIGHT * 4);

        for (int y = 0; y < LEVEL_HEIGHT; y++)
        {
            for (int x = 0; x < LEVEL_WIDTH; x++)
            {
                sf::Color color;
                if (GetCellType(level, {x, y}) == CellType::Empty)
                {
                    if ((x + y) % 2 == 0)
                        color = COLOR_GREEN_LIGHT;
                    else
                        color = COLOR_GREEN_DARK;
                }
                else if (GetCellType(level, {x, y}) == CellType::Wall)
                    color = COLOR_WALL;

                else if (GetCellType(level, {x, y}) == CellType::Snake)
                    color = COLOR_SNAKE;

                int index = (y * LEVEL_WIDTH + x) * 4;

                vertices[index + 0] = sf::Vertex(sf::Vector2f(x, y), color);
                vertices[index + 1] = sf::Vertex(sf::Vector2f(x + 1, y), color);
                vertices[index + 2] = sf::Vertex(sf::Vector2f(x + 1, y + 1), color);
                vertices[index + 3] = sf::Vertex(sf::Vector2f(x, y + 1), color);
            }
        }
        return vertices;
    }

    void SetCellType(LevelConfig &level, Position2D position, CellType cellType)
    {
        level.cells[position.x][position.y] = cellType;
    }

    CellType GetCellType(const LevelConfig &level, Position2D position)
    {
        return level.cells[position.x][position.y];
    }
}