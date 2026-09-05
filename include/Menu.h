#pragma once
#include <string>
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
    enum class MenuState
    {
        Main = 0,
        Pause,
        GameOver
    };

    enum class MenuActionType
    {
        SwitchMenuState = 0,
        SwitchGameState,
        StartGame
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
        std::vector<MenuItem> items;
        int selected = 0;
    };

    void InitMenues(std::map<MenuState, Menu> &menus);
}