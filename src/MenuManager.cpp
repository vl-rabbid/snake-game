#include "MenuManager.h"

namespace SnakeGame
{
    void MenuManager::Init(Resources &resources)
    {
        InitMenus(allMenus);
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
        if (layers.back().GetType() == MenuType::SubMenu && layers.size() > 1)
        {
            menuUi.DrawWindowTint(texture);
            DrawStates(layers[layers.size() - 2].GetState(), texture);
            menuUi.Draw(texture);
        }
        else
        {
            menuUi.DrawWindowTint(texture);
            DrawStates(layers.back().GetState(), texture);
            menuUi.Draw(texture);
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
            leaderboardManager.HandleInput(command, event);
            break;
        case MenuState::LevelSelect:
            levelMangager.HandleInput(command, event);
            break;
        case MenuState::GameOver:
            leaderboardManager.HandleInput(command, event);
            break;
        case MenuState::SetPlayerName:
            HandleTypingInput(command, event);
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

    void MenuManager::LoadMenu()
    {
        menuUi.Load(layers.back());
    }

    void MenuManager::LoadButtons()
    {
        menuUi.LoadButtons(layers.back());
    }

    void MenuManager::SetSelector()
    {
        menuUi.SetSelector(layers.back().GetSelected(), layers.back().GetFirstDisplayedItem());
    }

    bool MenuManager::PreviousMenu()
    {
        if (layers.size() > 1)
        {
            layers.pop_back();
            menuUi.Load(layers.back());
            return true;
        }
        return false;
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

    const LevelConfig &MenuManager::GetSelectedLevelConfig() const
    {
        return levelMangager.GetSelectedLevelConfig();
    }

    const std::string &MenuManager::GetInputString() const
    {
        return inputString;
    }

    void MenuManager::DrawStates(const MenuState &state, sf::RenderTexture &texture) const
    {
        switch (state)
        {
        case MenuState::LevelSelect:
            levelMangager.Draw(texture);
            break;
        case MenuState::Leaderboard:
            leaderboardManager.Draw(texture);
            break;
        case MenuState::GameOver:
            leaderboardManager.Draw(texture);
            break;
        default:
            break;
        }
    }

    void MenuManager::HandleTypingInput(MenuCommand &command, const sf::Event &event)
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
                    layers.back().SetInputItems(inputString);
                    menuUi.LoadButtons(layers.back());
                    command.action = MenuAction::MenuInput;
                }
            }
            else if (inputString.size() < 10 && IsAllowedInputChar(c))
            {
                inputString += static_cast<char>(c);
                menuUi.SetImputLabel(inputString);
                layers.back().SetInputItems(inputString);
                menuUi.LoadButtons(layers.back());
                command.action = MenuAction::MenuInput;
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
