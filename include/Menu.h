#pragma once
#include <string>
#include <SFML/Graphics.hpp>

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
        Resolution
    };

    enum class MenuActionType
    {
        SwitchMenuState = 0,
        SwitchGameState,
        StartGame,
        PreviousMenu
    };

    struct MenuItem
    {
        std::string label;
        MenuActionType actionType;
        int actionTarget;
    };

    struct Menu
    {
        std::string label;
        MenuType type;
        std::vector<MenuItem> items;
        int selected = 0;
        int firstDisplayedItem = 0;
    };

    void InitMenues(std::map<MenuState, Menu> &menus);
}