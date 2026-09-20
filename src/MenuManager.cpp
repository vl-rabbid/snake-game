#include "MenuManager.h"

namespace SnakeGame
{
    void MenuManager::Init(Resources &resources)
    {
        InitMenues(allMenus);
        levelMangager.Init(resources);
        leaderboardManager.Init(resources);
        menuUi.Init(resources);
    }

    void MenuManager::Update(const float deltaTime)
    {
        switch (layers.back().GetState())
        {
        case MenuState::LevelSelect:
            menuUi.Update(deltaTime);
            levelMangager.Update(deltaTime);
            break;
        case MenuState::SetPlayerName:
            menuUi.Update(deltaTime);
            menuUi.UpdateInputMarker(deltaTime);
            break;
        default:
            menuUi.Update(deltaTime);
            break;
        }
    }

    void MenuManager::Draw(sf::RenderTexture &texture) const
    {
        if (layers.back().GetType() == MenuType::FullMenu)
        {
            DrawMenu(layers.back(), texture);
        }
        else if (layers.size() > 1)
        {
            if (layers.back().GetType() == MenuType::SubMenu || layers.back().GetType() == MenuType::InputString)
            {
                DrawMenu(layers[layers.size() - 2], texture);
                DrawMenu(layers.back(), texture);
            }
        }
    }

    void MenuManager::SetState(const MenuState &state, const Config &gameConfig, const Leaderboard &gameLeaderboard)
    {
        if (state == MenuState::Main)
            ClearLayers();

        Menu menu;
        menu.SetConfig(allMenus[state]);
        layers.push_back(menu);

        Leaderboard leaderboard;
        switch (layers.back().GetState())
        {
        case MenuState::LevelSelect:
            levelMangager.LoadFromFiles();
            break;
        case MenuState::Pause:
            // PauseMusic(game);
            break;
        case MenuState::GameOver:
            leaderboardManager.LoadUI(gameLeaderboard);
            break;
        case MenuState::Leaderboard:
            leaderboard.LoadFromFile(levelMangager.GetSelectedLevelConfig());
            leaderboardManager.LoadUI(leaderboard);
            break;
        case MenuState::Resolution:
            SetMenuItems(gameConfig);
            break;
        case MenuState::Difficulty:
            SetMenuItems(gameConfig);
            break;
        case MenuState::Settings:
            SetMenuItems(gameConfig);
            break;
        case MenuState::SetPlayerName:
            inputString = gameConfig.playerName;
            menuUi.SetImputLabel(inputString);
            break;
        default:
            break;
        }
        menuUi.Load(layers.back());
    }

    MenuCommand MenuManager::HandleInput(const sf::Event &event)
    {
        MenuCommand command;
        command = layers.back().HandleInput(event);
        switch (layers.back().GetState())
        {
        case MenuState::Leaderboard:
            leaderboardManager.HandleInput(event);
            break;
        case MenuState::LevelSelect:
            levelMangager.HandleInput(event);
            if (command.action == MenuAction::StartGame)
                command.levelConfig = levelMangager.GetSelectedLevelConfig();
            break;
        case MenuState::GameOver:
            leaderboardManager.HandleInput(event);
            break;
        case MenuState::SetPlayerName:
            HandleTypingInput(event);
            if (command.action == MenuAction::SavePlayerName)
                command.inputString = inputString;
            break;
        default:
            break;
        }
        return command;
    }

    void MenuManager::ClearLayers()
    {
        layers.clear();
    }

    void MenuManager::ReloadUI(bool setSelector, bool loadButtons, bool loadMenu, bool previousMenu)
    {
        if (previousMenu)
        {
            if (layers.size() > 1)
            {
                layers.pop_back();
                menuUi.Load(layers.back());
            }
        }
        else if (loadMenu)
            menuUi.Load(layers.back());
        else if (loadButtons)
            menuUi.LoadButtons(layers.back());
        else if (setSelector)
            menuUi.SetSelector(layers.back().GetSelected());
    }

    void MenuManager::SetMenuItems(const Config &config)
    {
        switch (layers.back().GetState())
        {
        case MenuState::Resolution:
            layers.back().SetSubMenuItems(static_cast<int>(config.windowResolution));
            break;
        case MenuState::Difficulty:
            layers.back().SetSubMenuItems(static_cast<int>(config.difficulty));
            break;
        case MenuState::Settings:
            layers.back().SetSettingsItems(config.soundEnabled, config.musicEnabled);
            break;
        default:
            break;
        }
    }

    void MenuManager::DrawMenu(const Menu &menu, sf::RenderTexture &texture) const
    {
        switch (menu.GetState())
        {
        case MenuState::LevelSelect:
            menuUi.DrawWindowTint(texture);
            levelMangager.Draw(texture);
            menuUi.Draw(texture);
            break;
        case MenuState::Leaderboard:
            menuUi.DrawWindowTint(texture);
            leaderboardManager.Draw(texture);
            menuUi.Draw(texture);
            break;
        case MenuState::GameOver:
            menuUi.DrawWindowTint(texture);
            leaderboardManager.Draw(texture);
            menuUi.Draw(texture);
            break;
        default:
            menuUi.DrawWindowTint(texture);
            menuUi.Draw(texture);
            break;
        }
    }

    void MenuManager::HandleTypingInput(const sf::Event &event)
    {
        if (event.type == sf::Event::TextEntered)
        {
            char32_t c = event.text.unicode;
            if (c == '\b')
            {
                if (!inputString.empty())
                {
                    inputString.pop_back();
                    menuUi.SetImputLabel(inputString);
                    // PlaySound(game, game.soundFX, game.resources.input);
                    layers.back().SetInputItems(inputString);
                    menuUi.LoadButtons(layers.back());
                }
            }
            else if (inputString.size() < 10 && IsAllowedInputChar(c))
            {
                inputString += static_cast<char>(c);
                menuUi.SetImputLabel(inputString);
                // PlaySound(game, game.soundFX, game.resources.input);
                layers.back().SetInputItems(inputString);
                menuUi.LoadButtons(layers.back());
            }
        }
    }

    bool MenuManager::IsAllowedInputChar(char32_t c)
    {
        return (c >= U'A' && c <= U'Z') ||
               (c >= U'a' && c <= U'z') ||
               (c >= U'0' && c <= U'9') ||
               c == U'_' ||
               c == U'-';
    }
}
