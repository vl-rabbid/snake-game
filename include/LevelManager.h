#pragma once
#include "GameMath.h"
#include "LevelConfig.h"

namespace SnakeGame
{
    struct LevelManager
    {
        std::vector<LevelConfig> levels;
        int selected;
        int firstDisplayedItem;
    };

    void LoadLevelManager(LevelManager &levelMangager);
}
