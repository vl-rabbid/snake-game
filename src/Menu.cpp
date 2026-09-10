#include "Menu.h"
#include "GameState.h"
#include "Renderer.h"

namespace SnakeGame
{
    void InitMenues(std::map<MenuState, Menu> &menus)
    {
        menus[MenuState::Main] =
            {
                "Snake Game",
                MenuType::FullMenu,
                {{"Play",
                  MenuActionType::StartGame,
                  0},
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
                  static_cast<int>(ScreenResolution::R720x540)},
                 {"960x720",
                  MenuActionType::SetScreenScale,
                  static_cast<int>(ScreenResolution::R960x720)},
                 {"1200x900",
                  MenuActionType::SetScreenScale,
                  static_cast<int>(ScreenResolution::R1200x900)},
                 {"1440x1080",
                  MenuActionType::SetScreenScale,
                  static_cast<int>(ScreenResolution::R1440x1080)},
                 {"Back",
                  MenuActionType::PreviousMenu,
                  0}}};
    }
}
