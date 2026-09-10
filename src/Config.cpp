#include "Config.h"
#include <fstream>

namespace SnakeGame
{
    bool ConfigFileExists()
    {
        std::ifstream file(CONFIG_FILE_NAME);
        return file.good();
    }

    void InitConfig(Config &config)
    {
        SetDefaultConfig(config);
        if (ConfigFileExists())
        {
            LoadConfig(config);
        }
    }

    void SetDefaultConfig(Config &config)
    {
        config.difficulty = GameDifficulty::Normal;
        config.windowResolution = WindowResolution::R960x720;
    }

    bool LoadConfig(Config &config)
    {
        std::ifstream file(CONFIG_FILE_NAME);
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

                if (key == "difficulty")
                    config.difficulty = static_cast<GameDifficulty>(std::stoi(value));
                else if (key == "windowResolution")
                    config.windowResolution = static_cast<WindowResolution>(std::stoi(value));
            }
            file.close();

            return true;
        }
        return false;
    }

    bool SaveConfig(Config &config)
    {
        std::ofstream file(CONFIG_FILE_NAME);
        if (file.is_open())
        {
            file << "difficulty=" << static_cast<int>(config.difficulty) << "\n";
            file << "windowResolution=" << static_cast<int>(config.windowResolution) << "\n";
            return true;
        }
        return false;
    }
}