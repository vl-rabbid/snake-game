#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "StateManager.h"
#include "Config.h"
#include "MenuCommand.h"

namespace SnakeGame
{
    enum class MenuType
    {
        FullMenu = 0,
        SubMenu,
        InputString
    };

    struct MenuItem
    {
        std::string label;
        MenuAction action;
        int actionTarget;
        bool enabled = true;
        bool pressed = false;
    };

    struct MenuConfig
    {
        MenuState state;
        std::string title;
        MenuType type;
        std::vector<MenuItem> items;
        int displayedItemAmount = MAX_MENU_BUTTONS;
    };

    class Menu
    {
    public:
        MenuCommand HandleInput(const sf::Event &event);
        void SetConfig(const MenuConfig &menuConfig);
        void SetInputItems(const std::string &inputString);
        void SetSubMenuItems(int actionTarget);
        void SetSettingsItems(bool soundEnabled, bool musicEnabled);

        const MenuState &GetState() const;
        const MenuType &GetType() const;
        const std::string &GetTitle() const;
        const std::vector<MenuItem> &GetItems() const;
        int GetDisplayedItemAmount() const;
        int GetSelected() const;
        int GetFirstDisplayedItem() const;

    private:
        MenuConfig config;
        int selected = 0;
        int firstDisplayedItem = 0;
    };

    void InitMenues(std::map<MenuState, MenuConfig> &menus);
}