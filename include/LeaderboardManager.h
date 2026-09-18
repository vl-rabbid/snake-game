#pragma once
#include "UIComponents.h"
#include "Leaderboard.h"

namespace SnakeGame
{
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

    class LeaderboardManager
    {
    public:
        void Init(const Resources &resources);
        void Draw(sf::RenderTexture &texture) const;
        void HandleInput(const sf::Event &event);
        void LoadUI(const Leaderboard &leaderboard);

    private:
        void LoadUIEntries();

        int firstDisplayedItem = 0;
        std::vector<LeaderboardEntry> entries;
        LeaderboardUI ui;
    };
}
