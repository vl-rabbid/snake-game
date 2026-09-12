#include "LevelConfig.h"
#include <fstream>
#include <filesystem>

namespace SnakeGame
{
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