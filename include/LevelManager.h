#pragma once
#include "GameMath.h"

namespace SnakeGame
{
    enum class CellType
    {
        Empty = 0,
        Snake,
        Apple,
        Wall
    };

    struct LevelConfig
    {
        std::string id;
        std::string name;
        std::vector<Position2D> walls;
        Position2D snakeSpawn;
        int snakeSize;
        CellType cells[LEVEL_WIDTH][LEVEL_HEIGHT];
    };

    struct LevelManager
    {
        std::vector<LevelConfig> levels;
        int selected;
        int firstDisplayedItem;
    };

    void LoadLevelManager(LevelManager &levelMangager);
    void LoadLevel(LevelConfig &levelConfig, std::string filePath);
    void UpdateCellTypes(LevelConfig &levelConfig);
    void SetEmptyLevel(LevelConfig &levelConfig);
    sf::VertexArray GenerateLevelPreview(const LevelConfig &level);
    void SetCellType(LevelConfig &levelConfig, Position2D position, CellType cellType);
    CellType GetCellType(const LevelConfig &levelConfig, Position2D position);
}
