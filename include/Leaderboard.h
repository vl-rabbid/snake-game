#pragma once
#include <string>
#include "Constants.h"

namespace SnakeGame
{
    struct LeaderboardEntry
    {
        std::string playerName;
        int score;
    };

    struct Leaderboard
    {
        std::string levelId;
        std::vector<LeaderboardEntry> entries;
    };

    void AddLeaderboardEntry(Leaderboard &leaderboard, std::string playerName, int score);
    bool EntryExists(Leaderboard &leaderboard, LeaderboardEntry &entry);
    void SortLeaderboard(Leaderboard &leaderboard);
    bool LoadLeaderboard(Leaderboard &leaderboard, std::string levelId);
    bool SaveLeaderboard(Leaderboard &leaderboard);

}
