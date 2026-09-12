#include "Menu.h"

namespace SnakeGame
{
    void InitMenues(std::map<MenuState, Menu> &menus)
    {
        menus[MenuState::Main] =
            {
                "Snake Game",
                MenuType::FullMenu,
                {{"Play",
                  MenuActionType::SwitchGameState,
                  static_cast<int>(GameState::LevelSelect)},
                 {"Settings",
                  MenuActionType::SwitchMenuState,
                  static_cast<int>(MenuState::Settings)},
                 {"Exit Game",
                  MenuActionType::SwitchGameState,
                  static_cast<int>(GameState::Exit)}}};

        menus[MenuState::Pause] =
            {
                "Pause",
                MenuType::FullMenu,
                {{"Resume",
                  MenuActionType::SwitchGameState,
                  static_cast<int>(GameState::GameLoop)},
                 {"Restart",
                  MenuActionType::StartGame,
                  0},
                 {"Back to menu",
                  MenuActionType::SwitchGameState,
                  static_cast<int>(GameState::MainMenu)}}};

        menus[MenuState::GameOver] =
            {
                "GAME OVER",
                MenuType::FullMenu,
                {{"Restart",
                  MenuActionType::StartGame,
                  0},
                 {"Back to menu",
                  MenuActionType::SwitchGameState,
                  static_cast<int>(GameState::MainMenu)}}};

        menus[MenuState::Settings] =
            {
                "Settings",
                MenuType::FullMenu,
                {{"Resolution",
                  MenuActionType::SwitchMenuState,
                  static_cast<int>(MenuState::Resolution)},
                 {"Back",
                  MenuActionType::PreviousMenu,
                  0}}};

        menus[MenuState::Resolution] =
            {
                "Resolution",
                MenuType::SubMenu,
                {{"720x540",
                  MenuActionType::SetScreenScale,
                  static_cast<int>(WindowResolution::R720x540)},
                 {"960x720",
                  MenuActionType::SetScreenScale,
                  static_cast<int>(WindowResolution::R960x720)},
                 {"1200x900",
                  MenuActionType::SetScreenScale,
                  static_cast<int>(WindowResolution::R1200x900)},
                 {"1440x1080",
                  MenuActionType::SetScreenScale,
                  static_cast<int>(WindowResolution::R1440x1080)},
                 {"Back",
                  MenuActionType::PreviousMenu,
                  0}}};

        menus[MenuState::Difficulty] =
            {
                "Difficulty",
                MenuType::SubMenu,
                {{"Very Easy",
                  MenuActionType::SetDifficulty,
                  static_cast<int>(GameDifficulty::VeryEasy)},
                 {"Easy",
                  MenuActionType::SetDifficulty,
                  static_cast<int>(GameDifficulty::Easy)},
                 {"Normal",
                  MenuActionType::SetDifficulty,
                  static_cast<int>(GameDifficulty::Normal)},
                 {"Hard",
                  MenuActionType::SetDifficulty,
                  static_cast<int>(GameDifficulty::Hard)},
                 {"Very Hard",
                  MenuActionType::SetDifficulty,
                  static_cast<int>(GameDifficulty::VeryHard)},
                 {"Back",
                  MenuActionType::PreviousMenu,
                  0}}};

        menus[MenuState::LevelSelect] =
            {
                "",
                MenuType::FullMenu,
                {{"Start Game",
                  MenuActionType::StartGame,
                  0},
                 {"Difficulty",
                  MenuActionType::SwitchMenuState,
                  static_cast<int>(MenuState::Difficulty)},
                 {"Back to menu",
                  MenuActionType::SwitchGameState,
                  static_cast<int>(GameState::MainMenu)}},
                2};
    }
}
