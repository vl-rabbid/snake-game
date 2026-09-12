#include "Leaderboard.h"
#include <fstream>
#include <filesystem>

namespace SnakeGame
{
    void AddLeaderboardEntry(Leaderboard &leaderboard, std::string playerName, int score)
    {
        LeaderboardEntry entry;
        entry.playerName = playerName;
        entry.score = score;
        if (!EntryExists(leaderboard, entry))
        {
            leaderboard.entries.push_back(entry);

            SortLeaderboard(leaderboard);
            if (leaderboard.entries.size() > LEADERBOARD_SIZE)
                leaderboard.entries.resize(LEADERBOARD_SIZE);
        }
    }

    bool EntryExists(Leaderboard &leaderboard, LeaderboardEntry &entry)
    {
        for (int i = 0; i < leaderboard.entries.size(); i++)
        {
            if (leaderboard.entries[i].playerName == entry.playerName && leaderboard.entries[i].score == entry.score)
            {
                return true;
            }
        }
        return false;
    }

    void SortLeaderboard(Leaderboard &leaderboard)
    {
        std::sort(
            leaderboard.entries.begin(),
            leaderboard.entries.end(),
            [](const LeaderboardEntry &a, const LeaderboardEntry &b)
            {
                return a.score > b.score;
            });
    }

    bool LoadLeaderboard(Leaderboard &leaderboard, std::string levelId)
    {
        leaderboard.levelId = levelId;
        leaderboard.entries.clear();
        leaderboard.entries.reserve(LEADERBOARD_SIZE);

        std::ifstream file("leaderboards/" + levelId + ".lb");
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

                LeaderboardEntry entry;
                entry.playerName = key;
                entry.score = std::stoi(value);
                leaderboard.entries.push_back(entry);
            }
            if (leaderboard.entries.size() > LEADERBOARD_SIZE)
                leaderboard.entries.resize(LEADERBOARD_SIZE);

            file.close();
            return true;
        }
        return false;
    }

    bool SaveLeaderboard(Leaderboard &leaderboard)
    {
        const std::filesystem::path directory = "leaderboards";
        std::filesystem::create_directories(directory);
        std::ofstream file("leaderboards/" + leaderboard.levelId + ".lb");
        if (file.is_open())
        {
            for (int i = 0; i < leaderboard.entries.size(); i++)
            {
                file << leaderboard.entries[i].playerName << "=" << leaderboard.entries[i].score << "\n";
            }
            file.close();
            return true;
        }
        return false;
    }
}