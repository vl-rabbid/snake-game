#pragma once
#include "LevelConfig.h"

namespace SnakeGame
{
    enum class MenuAction
    {
        Empty = 0,
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

        LevelConfig levelConfig;
        std::string inputString;

        bool setSelector;
        bool loadButtons;
        bool loadMenu;
        bool previousMenu;
    };

}
