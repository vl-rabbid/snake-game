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
                    LevelConfig level;
                    level.LoadFromFile(entry.path().string());
                    levelMangager.levels.push_back(level);
                }
            }
        }

        if (levelMangager.levels.size() == 0)
        {
            LevelConfig level;
            level.SetEmpty();
            level.UpdatePreviewCells();
            levelMangager.levels.push_back(level);
        }
    }
}