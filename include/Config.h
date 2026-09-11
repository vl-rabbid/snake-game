#pragma once
#include "Constants.h"

namespace SnakeGame
{
    enum class GameDifficulty
    {
        VeryEasy = 4,
        Easy = 5,
        Normal = 6,
        Hard = 8,
        VeryHard = 9
    };

    enum class WindowResolution
    {
        R720x540 = 3,
        R960x720 = 4,
        R1200x900 = 5,
        R1440x1080 = 6
    };

    struct Config
    {
        GameDifficulty difficulty;
        WindowResolution windowResolution;
        std::string playerName;
    };

    bool ConfigFileExists();
    void InitConfig(Config &config);
    void SetDefaultConfig(Config &config);
    bool LoadConfig(Config &config);
    bool SaveConfig(Config &config);

}
