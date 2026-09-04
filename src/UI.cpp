#include "UI.h"
#include "GameMath.h"
#include <cassert>

namespace SnakeGame
{
    void InitUI(UI &ui)
    {
        assert(ui.font.loadFromFile(std::string(RESOURCES_PATH) + "/Fonts/Roboto-Regular.ttf"));

        ui.menuLabel.setString("menuLabel");
        ui.menuLabel.setFont(ui.font);
        ui.menuLabel.setStyle(sf::Text::Bold);
        ui.menuLabel.setCharacterSize(100);
        ui.menuLabel.setFillColor(sf::Color::White);
        SetTextRelativeOrigin(ui.menuLabel, 0.5f, 0.5f);
        SetTextRelativePosition(ui.menuLabel, LEVEL_WIDTH, LEVEL_HEIGHT, 0.5f, 0.2f);

        ui.menuButtons.clear();
        ui.menuButtons.resize(NUM_MENU_BUTTONS);
        for (size_t i = 0; i < ui.menuButtons.size(); ++i)
        {
            ui.menuButtons[i].label.setString("button " + std::to_string(i));
            ui.menuButtons[i].label.setFont(ui.font);
            ui.menuButtons[i].label.setCharacterSize(32);
            ui.menuButtons[i].label.setFillColor(sf::Color::White);
            SetTextRelativePosition(ui.menuButtons[i].label, LEVEL_WIDTH, LEVEL_HEIGHT, 0.5f, 0.6f);
            ShiftTextPozition(ui.menuButtons[i].label, 0.f, 50.f * i);
        }
    }

    void UpdateMenuUI(UI &ui, Menu &menu)
    {
        ui.menuLabel.setString(menu.label);
        for (int i = 0; i < ui.menuButtons.size(); i++)
        {
            if (i < menu.items.size())
            {
                ui.menuButtons[i].label.setString(menu.items[i].label);
                SetTextRelativeOrigin(ui.menuButtons[i].label, 0.5f, 0.5f);
            }
        }
        UpdateSelectedItem(ui, menu);
    }

    void UpdateSelectedItem(UI &ui, Menu &menu)
    {
        for (int i = 0; i < menu.items.size(); i++)
        {
            if (i == menu.selected)
            {
                ui.menuButtons[i].label.setFillColor(sf::Color::Green);
            }
            else
            {
                ui.menuButtons[i].label.setFillColor(sf::Color::White);
            }
        };
    }

    void DrawMenuUI(UI &ui, Menu &menu, sf::RenderWindow &window)
    {
        window.draw(ui.menuLabel);
        for (int i = 0; i < menu.items.size(); ++i)
        {
            window.draw(ui.menuButtons[i].label);
        }
    }

}