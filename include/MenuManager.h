#pragma once
#include "LevelManager.h"
#include "LeaderboardManager.h"
#include "MenuUI.h"
#include "Menu.h"
#include "MenuCommand.h"

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
        void ReloadUI(bool setSelector, bool loadButtons, bool loadMenu, bool previousMenu);
        void SetMenuItems(const Config &config);

    private:
        void DrawMenu(const Menu &menu, sf::RenderTexture &texture) const;
        void HandleTypingInput(const sf::Event &event, SoundID &sound);
        bool IsAllowedInputChar(char32_t c);

        std::vector<Menu> layers;
        std::map<MenuState, MenuConfig> allMenus;

        MenuUI menuUi;
        LevelManager levelMangager;
        LeaderboardManager leaderboardManager;
        std::string inputString;
    };
}
