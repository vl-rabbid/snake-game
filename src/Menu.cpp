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
                  MenuActionType::StartGame,
                  0},
                 {"Exit Game",
                  MenuActionType::SwitchGameState,
                  static_cast<int>(GameState::Exit)}}};

        menus[MenuState::Pause] =
            {
                "Pause",
                {{"Resume",
                  MenuActionType::SwitchGameState,
                  static_cast<int>(GameState::GameLoop)},
                 {"Restart",
                  MenuActionType::StartGame,
                  0},
                 {"Back to main menu",
                  MenuActionType::SwitchGameState,
                  static_cast<int>(GameState::MainMenu)}}};

        menus[MenuState::GameOver] =
            {
                "GAME OVER",
                {{"Restart",
                  MenuActionType::StartGame,
                  0},
                 {"Back to main menu",
                  MenuActionType::SwitchGameState,
                  static_cast<int>(GameState::MainMenu)}}};
    }
}