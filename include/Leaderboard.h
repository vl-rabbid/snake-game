#pragma once
#include <string>
#include "Constants.h"
#include "LevelConfig.h"

namespace SnakeGame
{
    struct LeaderboardEntry
    {
        std::string playerName;
        int score;
    };

    class Leaderboard
    {
    public:
        bool LoadFromFile(const LevelConfig &levelConfig);
        void AddEntry(const std::string &playerName, int score);
        const std::string &GetLevelName() const;
        const sf::VertexArray &GetLevelPreview() const;
        const std::vector<LeaderboardEntry> &GetEntries() const;

    private:
        bool DoesEntryExists(const LeaderboardEntry &entry) const;
        void Sort();
        bool SaveToFile();

        std::string levelId;
        std::string levelName;
        sf::VertexArray levelPreview;
        std::vector<LeaderboardEntry> entries;
    };
}
