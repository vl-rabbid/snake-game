#pragma once
#include <string>
#include "Constants.h"
#include "UIComponents.h"
#include "LevelConfig.h"

namespace SnakeGame
{
    struct LeaderboardEntry
    {
        std::string playerName;
        int score;
    };

    struct LeaderboardUI
    {
        sf::Sprite background;
        sf::Sprite titleFrame;
        sf::Text title;
        sf::Text entry[LEADERBOARD_DISPLAYED];
        sf::Sprite arrowRight;
        sf::Sprite arrowLeft;
        LevelButton levelButton;
    };

    class Leaderboard
    {
    public:
        void Init(const Resources &resources);
        void Draw(sf::RenderTexture &texture) const;
        void HandleInput(const sf::Event &event);
        bool LoadFromFile(const LevelConfig &levelConfig);
        void AddEntry(const std::string &playerName, int score);
        void LoadUI();

    private:
        void LoadUIEntries();
        bool DoesEntryExists(const LeaderboardEntry &entry) const;
        void Sort();
        bool SaveToFile();

        std::string levelId;
        std::string levelName;
        sf::VertexArray levelPreview;
        std::vector<LeaderboardEntry> entries;
        int firstDisplayedItem = 0;
        LeaderboardUI ui;
    };
}
