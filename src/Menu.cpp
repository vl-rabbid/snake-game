#include "Menu.h"
#include "GameState.h"

namespace SnakeGame
{
    void InitMenues(std::map<MenuState, Menu> &menus)
    {
        menus[MenuState::Main] =
            {
                "Snake Game",
                {{"Play",
                  MenuActionType::SwitchGameState,
                  static_cast<int>(GameState::GameLoop)},
                 {"Exit Game",
                  MenuActionType::SwitchGameState,
                  static_cast<int>(GameState::Exit)}}};

        menus[MenuState::Pause] =
            {
                "Pause",
                {{"Resume",
                  MenuActionType::SwitchGameState,
                  static_cast<int>(GameState::GameLoop)},
                 {"Back to main menu",
                  MenuActionType::SwitchGameState,
                  static_cast<int>(GameState::MainMenu)}}};

        menus[MenuState::GameOver] =
            {
                "Pause",
                {{"Restart",
                  MenuActionType::RestartGame,
                  0},
                 {"Back to main menu",
                  MenuActionType::SwitchGameState,
                  static_cast<int>(GameState::MainMenu)}}};
    }
}