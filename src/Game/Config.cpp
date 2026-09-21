#include "Game/Config.h"
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
        config.playerName = "XYZ";
        config.soundEnabled = true;
        config.musicEnabled = true;
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
                else if (key == "playerName")
                    config.playerName = value;
                else if (key == "soundEnabled")
                    config.soundEnabled = static_cast<bool>(std::stoi(value));
                else if (key == "musicEnabled")
                    config.musicEnabled = static_cast<bool>(std::stoi(value));
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
            file << "playerName=" << config.playerName << "\n";
            file << "soundEnabled=" << static_cast<int>(config.soundEnabled) << "\n";
            file << "musicEnabled=" << static_cast<int>(config.musicEnabled) << "\n";
            file.close();
            return true;
        }
        return false;
    }
}