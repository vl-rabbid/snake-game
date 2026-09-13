#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "GameState.h"
#include "Config.h"

namespace SnakeGame
{
    enum class MenuType
    {
        FullMenu = 0,
        SubMenu
    };

    enum class MenuState
    {
        Main = 0,
        Pause,
        GameOver,
        Settings,
        Resolution,
        Difficulty,
        LevelSelect,
        Leaderboard
    };

    enum class MenuActionType
    {
        SwitchMenuState = 0,
        SwitchGameState,
        StartGame,
        PreviousMenu,
        SetScreenScale,
        SetDifficulty
    };

    struct MenuItem
    {
        std::string label;
        MenuActionType actionType;
        int actionTarget;
        bool enabled = true;
        bool pressed = false;
    };

    struct Menu
    {
        std::string label;
        MenuType type;
        std::vector<MenuItem> items;
        int displayedItemAmount = MAX_MENU_BUTTONS;
        int selected = 0;
        int firstDisplayedItem = 0;
    };

    void InitMenues(std::map<MenuState, Menu> &menus);
}