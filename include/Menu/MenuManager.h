#pragma once
#include "Menu/LevelSelect.h"
#include "Menu/LeaderboardView.h"
#include "Menu/MenuUI.h"
#include "Menu/Menu.h"
#include "Menu/MenuCommand.h"

namespace SnakeGame
{
    class MenuManager
    {
    public:
        void Init(Resources &resources);
        void Update(const float deltaTime);
        void Draw(sf::RenderTexture &texture) const;
        void SetState(const MenuState &state, const Config &gameConfig, const Leaderboard &gameLeaderboard);
        MenuCommand HandleInput(const sf::Event &event);
        void ClearLayers();
        void LoadMenu();
        void LoadButtons();
        void SetSelector();
        bool PreviousMenu();
        void SetMenuItems(const Config &config);
        const LevelConfig &GetSelectedLevelConfig() const;
        const std::string &GetInputString() const;

    private:
        void DrawStates(const MenuState &state, sf::RenderTexture &texture) const;
        void HandleTypingInput(MenuCommand &command, const sf::Event &event);
        bool IsAllowedInputChar(char32_t c);

        std::vector<Menu> layers;
        std::map<MenuState, MenuConfig> allMenus;

        MenuUI menuUi;
        LevelSelect levelSelect;
        LeaderboardView leaderboardView;
        std::string inputString;
    };
}
