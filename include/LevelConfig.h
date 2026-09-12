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

    void LoadLevel(LevelConfig &levelConfig, std::string filePath);
    void SetEmptyLevel(LevelConfig &levelConfig);
    sf::VertexArray GenerateLevelPreview(const LevelConfig &level);
    void SetCellType(LevelConfig &levelConfig, Position2D position, CellType cellType);
    CellType GetCellType(const LevelConfig &levelConfig, Position2D position);
}
