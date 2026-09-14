#include "Menu.h"

namespace SnakeGame
{
    void InitMenues(std::map<MenuState, Menu> &menus)
    {
        menus[MenuState::Main] =
            {
                MenuState::Main,
                "Snake Game",
                MenuType::FullMenu,
                {{"Play",
                  MenuActionType::SwitchMenuState,
                  static_cast<int>(MenuState::LevelSelect)},
                 {"Settings",
                  MenuActionType::SwitchMenuState,
                  static_cast<int>(MenuState::Settings)},
                 {"Exit Game",
                  MenuActionType::SwitchGameState,
                  static_cast<int>(GameState::Exit)}}};

        menus[MenuState::Pause] =
            {
                MenuState::Pause,
                "Pause",
                MenuType::FullMenu,
                {{"Resume",
                  MenuActionType::ResumeGame,
                  0},
                 {"Restart",
                  MenuActionType::StartGame,
                  0},
                 {"Settings",
                  MenuActionType::SwitchMenuState,
                  static_cast<int>(MenuState::Settings)},
                 {"Back to menu",
                  MenuActionType::SwitchMenuState,
                  static_cast<int>(MenuState::Main)}}};

        menus[MenuState::GameOver] =
            {
                MenuState::GameOver,
                "",
                MenuType::FullMenu,
                {{"Restart",
                  MenuActionType::StartGame,
                  0},
                 {"Difficulty",
                  MenuActionType::SwitchMenuState,
                  static_cast<int>(MenuState::Difficulty)},
                 {"Back to menu",
                  MenuActionType::SwitchMenuState,
                  static_cast<int>(MenuState::Main)}},
                2};

        menus[MenuState::Settings] =
            {
                MenuState::Settings,
                "Settings",
                MenuType::FullMenu,
                {{"Resolution",
                  MenuActionType::SwitchMenuState,
                  static_cast<int>(MenuState::Resolution)},
                 {"Player name",
                  MenuActionType::SwitchMenuState,
                  static_cast<int>(MenuState::SetPlayerName)},
                 {"Sound",
                  MenuActionType::ToggleSound,
                  0},
                 {"Music",
                  MenuActionType::ToggleMusic,
                  0},
                 {"Back",
                  MenuActionType::PreviousMenu,
                  0}}};

        menus[MenuState::Resolution] =
            {
                MenuState::Resolution,
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
                MenuState::Difficulty,
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
                MenuState::LevelSelect,
                "",
                MenuType::FullMenu,
                {{"Start Game",
                  MenuActionType::StartGame,
                  0},
                 {"Difficulty",
                  MenuActionType::SwitchMenuState,
                  static_cast<int>(MenuState::Difficulty)},
                 {"Leaderboard",
                  MenuActionType::SwitchMenuState,
                  static_cast<int>(MenuState::Leaderboard)},
                 {"Back",
                  MenuActionType::PreviousMenu,
                  0}},
                2};

        menus[MenuState::Leaderboard] =
            {
                MenuState::Leaderboard,
                "",
                MenuType::FullMenu,
                {{"Back",
                  MenuActionType::PreviousMenu,
                  0}},
                2};

        menus[MenuState::SetPlayerName] =
            {
                MenuState::SetPlayerName,
                "Player name",
                MenuType::InputString,
                {{"Save",
                  MenuActionType::SavePlayerName,
                  0},
                 {"Back",
                  MenuActionType::PreviousMenu,
                  0}},
                3};
    }
}
