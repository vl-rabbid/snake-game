#include "Menu.h"

namespace SnakeGame
{
    MenuCommand Menu::HandleInput(const sf::Event &event)
    {
        MenuCommand command;
        command.action = MenuAction::Empty;
        command.setSelector = false;
        command.loadButtons = false;
        command.loadMenu = false;
        command.previousMenu = false;

        static bool enterHeld = false;
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
        {
            if (!config.items[selected].pressed)
            {
                config.items[selected].pressed = true;
                enterHeld = true;
                command.loadButtons = true;
            }
            return command;
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            if (config.state == MenuState::Pause)
                command.action = MenuAction::ResumeGame;
            else
                command.previousMenu = true;
            return command;
        }
        else if (!enterHeld && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
        {
            int previousItem = selected;
            selected -= 1;
            if (selected < 0)
                selected = config.items.size() - 1;

            if (selected >= firstDisplayedItem + config.displayedItemAmount)
            {
                firstDisplayedItem = selected - config.displayedItemAmount + 1;
                command.loadButtons = true;
            }
            else if ((selected < firstDisplayedItem))
            {
                firstDisplayedItem = selected;
                command.loadButtons = true;
            }
            else
                command.setSelector = true;

            // if (previousItem != selected)
            //     PlaySound(game, game.soundFX, game.resources.uiMoveVertical);

            return command;
        }
        else if (!enterHeld && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
        {
            int previousItem = selected;
            selected += 1;
            if (selected > config.items.size() - 1)
            {
                selected = 0;
            }

            if (selected >= firstDisplayedItem + config.displayedItemAmount)
            {
                firstDisplayedItem = selected - config.displayedItemAmount + 1;
                command.loadButtons = true;
            }
            else if ((selected < firstDisplayedItem))
            {
                firstDisplayedItem = selected;
                command.loadButtons = true;
            }
            else
                command.setSelector = true;

            // if (previousItem != selected)
            //     PlaySound(game, game.soundFX, game.resources.uiMoveVertical);

            return command;
        }
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
        {
            enterHeld = false;
            config.items[selected].pressed = false;
            if (config.items[selected].enabled)
            {
                switch (config.items[selected].action)
                {
                case MenuAction::PreviousMenu:
                    command.previousMenu = true;
                    break;
                case MenuAction::SetScreenScale:
                    command.previousMenu = true;
                    break;
                case MenuAction::SetDifficulty:
                    command.previousMenu = true;
                    break;
                case MenuAction::ToggleSound:
                    command.loadButtons = true;
                    break;
                case MenuAction::ToggleMusic:
                    command.loadButtons = true;
                    break;
                case MenuAction::SavePlayerName:
                    command.previousMenu = true;
                    break;
                default:
                    break;
                }
                // PlaySound(game, game.soundFX, game.resources.uiSelect);
                command.action = config.items[selected].action;
                command.actionTarget = config.items[selected].actionTarget;
            }
            return command;
        };
        return command;
    }

    void Menu::SetConfig(const MenuConfig &menuConfig)
    {
        config = menuConfig;
    }

    void Menu::SetInputItems(const std::string &inputString)
    {
        for (auto &item : config.items)
        {
            if (item.action == MenuAction::SavePlayerName)
            {
                if (inputString.empty())
                    item.enabled = false;
                else
                    item.enabled = true;
            }
        }
    }

    void Menu::SetSubMenuItems(int actionTarget)
    {
        for (int i = 0; i < config.items.size(); i++)
        {
            if (config.items[i].actionTarget == actionTarget)
            {
                config.items[i].enabled = false;
            }
            else
            {
                config.items[i].enabled = true;
            }
        }
    }

    void Menu::SetSettingsItems(bool soundEnabled, bool musicEnabled)
    {
        for (int i = 0; i < config.items.size(); i++)
        {
            switch (config.items[i].action)
            {
            case MenuAction::ToggleSound:
                if (soundEnabled)
                    config.items[i].label = "Sound: ON";
                else
                    config.items[i].label = "Sound: OFF";
                break;
            case MenuAction::ToggleMusic:
                if (musicEnabled)
                    config.items[i].label = "Music: ON";
                else
                    config.items[i].label = "Music: OFF";
                break;
            default:
                break;
            }
        }
    }

    const MenuState &Menu::GetState() const
    {
        return config.state;
    }

    const MenuType &Menu::GetType() const
    {
        return config.type;
    }

    const std::string &Menu::GetTitle() const
    {
        return config.title;
    }

    const std::vector<MenuItem> &Menu::GetItems() const
    {
        return config.items;
    }

    int Menu::GetDisplayedItemAmount() const
    {
        return config.displayedItemAmount;
    }

    int Menu::GetSelected() const
    {
        return selected;
    }

    int Menu::GetFirstDisplayedItem() const
    {
        return firstDisplayedItem;
    }

    void InitMenues(std::map<MenuState, MenuConfig> &menus)
    {
        menus[MenuState::Main] =
            {
                MenuState::Main,
                "Snake Game",
                MenuType::FullMenu,
                {{"Play",
                  MenuAction::SwitchMenuState,
                  static_cast<int>(MenuState::LevelSelect)},
                 {"Settings",
                  MenuAction::SwitchMenuState,
                  static_cast<int>(MenuState::Settings)},
                 {"Exit Game",
                  MenuAction::ExitApplication,
                  0}}};

        menus[MenuState::Pause] =
            {
                MenuState::Pause,
                "Pause",
                MenuType::FullMenu,
                {{"Resume",
                  MenuAction::ResumeGame,
                  0},
                 {"Restart",
                  MenuAction::ResetGame,
                  0},
                 {"Settings",
                  MenuAction::SwitchMenuState,
                  static_cast<int>(MenuState::Settings)},
                 {"Back to menu",
                  MenuAction::SwitchMenuState,
                  static_cast<int>(MenuState::Main)}}};

        menus[MenuState::GameOver] =
            {
                MenuState::GameOver,
                "",
                MenuType::FullMenu,
                {{"Restart",
                  MenuAction::ResetGame,
                  0},
                 {"Difficulty",
                  MenuAction::SwitchMenuState,
                  static_cast<int>(MenuState::Difficulty)},
                 {"Back to menu",
                  MenuAction::SwitchMenuState,
                  static_cast<int>(MenuState::Main)}},
                2};

        menus[MenuState::Settings] =
            {
                MenuState::Settings,
                "Settings",
                MenuType::FullMenu,
                {{"Resolution",
                  MenuAction::SwitchMenuState,
                  static_cast<int>(MenuState::Resolution)},
                 {"Player name",
                  MenuAction::SwitchMenuState,
                  static_cast<int>(MenuState::SetPlayerName)},
                 {"Sound",
                  MenuAction::ToggleSound,
                  0},
                 {"Music",
                  MenuAction::ToggleMusic,
                  0},
                 {"Back",
                  MenuAction::PreviousMenu,
                  0}}};

        menus[MenuState::Resolution] =
            {
                MenuState::Resolution,
                "Resolution",
                MenuType::SubMenu,
                {{"720x540",
                  MenuAction::SetScreenScale,
                  static_cast<int>(WindowResolution::R720x540)},
                 {"960x720",
                  MenuAction::SetScreenScale,
                  static_cast<int>(WindowResolution::R960x720)},
                 {"1200x900",
                  MenuAction::SetScreenScale,
                  static_cast<int>(WindowResolution::R1200x900)},
                 {"1440x1080",
                  MenuAction::SetScreenScale,
                  static_cast<int>(WindowResolution::R1440x1080)},
                 {"Back",
                  MenuAction::PreviousMenu,
                  0}}};

        menus[MenuState::Difficulty] =
            {
                MenuState::Difficulty,
                "Difficulty",
                MenuType::SubMenu,
                {{"Very Easy",
                  MenuAction::SetDifficulty,
                  static_cast<int>(GameDifficulty::VeryEasy)},
                 {"Easy",
                  MenuAction::SetDifficulty,
                  static_cast<int>(GameDifficulty::Easy)},
                 {"Normal",
                  MenuAction::SetDifficulty,
                  static_cast<int>(GameDifficulty::Normal)},
                 {"Hard",
                  MenuAction::SetDifficulty,
                  static_cast<int>(GameDifficulty::Hard)},
                 {"Very Hard",
                  MenuAction::SetDifficulty,
                  static_cast<int>(GameDifficulty::VeryHard)},
                 {"Back",
                  MenuAction::PreviousMenu,
                  0}}};

        menus[MenuState::LevelSelect] =
            {
                MenuState::LevelSelect,
                "",
                MenuType::FullMenu,
                {{"Start Game",
                  MenuAction::StartGame,
                  0},
                 {"Difficulty",
                  MenuAction::SwitchMenuState,
                  static_cast<int>(MenuState::Difficulty)},
                 {"Leaderboard",
                  MenuAction::SwitchMenuState,
                  static_cast<int>(MenuState::Leaderboard)},
                 {"Back",
                  MenuAction::PreviousMenu,
                  0}},
                2};

        menus[MenuState::Leaderboard] =
            {
                MenuState::Leaderboard,
                "",
                MenuType::FullMenu,
                {{"Back",
                  MenuAction::PreviousMenu,
                  0}},
                2};

        menus[MenuState::SetPlayerName] =
            {
                MenuState::SetPlayerName,
                "Player name",
                MenuType::InputString,
                {{"Save",
                  MenuAction::SavePlayerName,
                  0},
                 {"Back",
                  MenuAction::PreviousMenu,
                  0}},
                3};
    }
}
