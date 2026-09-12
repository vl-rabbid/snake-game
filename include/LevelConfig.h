#pragma once
#include <string>
#include <vector>
#include "GameMath.h"

namespace SnakeGame
{

    struct LevelConfig
    {
        std::string id;
        std::string name;
        std::vector<Position2D> walls;
        Position2D snakeSpawn;
        int snakeSize;
    };

    void LoadLevel(LevelConfig &levelConfig, std::string filePath);
    void SetEmptyLevel(LevelConfig &levelConfig);
}
