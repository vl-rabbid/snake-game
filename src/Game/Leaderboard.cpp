#include "Game/Leaderboard.h"
#include <fstream>
#include <filesystem>

namespace SnakeGame
{
    bool Leaderboard::LoadFromFile(const LevelConfig &levelConfig)
    {
        levelId = levelConfig.GetId();
        levelName = levelConfig.GetName();
        levelPreview = levelConfig.GenerateLevelPreview();
        entries.clear();
        entries.reserve(LEADERBOARD_SIZE);

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
                entries.push_back(entry);
            }
            if (entries.size() > LEADERBOARD_SIZE)
                entries.resize(LEADERBOARD_SIZE);

            file.close();
            return true;
        }
        return false;
    }

    void Leaderboard::AddEntry(const std::string &playerName, int score)
    {
        LeaderboardEntry entry;
        entry.playerName = playerName;
        entry.score = score;
        if (!DoesEntryExists(entry))
        {
            entries.push_back(entry);
            Sort();
            if (entries.size() > LEADERBOARD_SIZE)
                entries.resize(LEADERBOARD_SIZE);
        }
        SaveToFile();
    }

    const std::string &Leaderboard::GetLevelName() const
    {
        return levelName;
    }

    const sf::VertexArray &Leaderboard::GetLevelPreview() const
    {
        return levelPreview;
    }

    const std::vector<LeaderboardEntry> &Leaderboard::GetEntries() const
    {
        return entries;
    }

    bool Leaderboard::DoesEntryExists(const LeaderboardEntry &entry) const
    {
        for (int i = 0; i < entries.size(); i++)
            if (entries[i].playerName == entry.playerName && entries[i].score == entry.score)
                return true;

        return false;
    }

    void Leaderboard::Sort()
    {
        std::sort(
            entries.begin(),
            entries.end(),
            [](const LeaderboardEntry &a, const LeaderboardEntry &b)
            {
                return a.score > b.score;
            });
    }

    bool Leaderboard::SaveToFile()
    {
        const std::filesystem::path directory = "leaderboards";
        std::filesystem::create_directories(directory);
        std::ofstream file("leaderboards/" + levelId + ".lb");
        if (file.is_open())
        {
            for (int i = 0; i < entries.size(); i++)
            {
                file << entries[i].playerName << "=" << entries[i].score << "\n";
            }
            file.close();
            return true;
        }
        return false;
    }
}