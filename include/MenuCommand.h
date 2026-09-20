#pragma once
#include "LevelConfig.h"
#include "Resources.h"

namespace SnakeGame
{
    enum class MenuAction
    {
        None = 0,

        MenuMoveVertical,
        MenuMoveHorizontal,
        MenuInput,
        MenuPress,

        SwitchMenuState,
        SwitchGameState,
        StartGame,
        ResetGame,
        ResumeGame,
        PreviousMenu,
        SetScreenScale,
        SetDifficulty,
        ToggleSound,
        ToggleMusic,
        SavePlayerName,
        ExitApplication
    };

    struct MenuCommand
    {
        MenuAction action;
        int actionTarget;
    };

}
