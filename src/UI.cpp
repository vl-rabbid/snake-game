#include "UI.h"
#include "GameMath.h"

namespace SnakeGame
{
    void InitUI(UI &ui, Resources &resources)
    {
        ui.menuLabel.setString("menuLabel");
        ui.menuLabel.setFont(resources.font);
        ui.menuLabel.setStyle(sf::Text::Bold);
        ui.menuLabel.setCharacterSize(30);
        ui.menuLabel.setFillColor(sf::Color::White);
        SetTextRelativePosition(ui.menuLabel, 0.5f, 0.2f);

        ui.menuButtons.clear();
        ui.menuButtons.resize(NUM_MENU_BUTTONS);
        for (size_t i = 0; i < ui.menuButtons.size(); ++i)
        {
            ui.menuButtons[i].label.setString("button " + std::to_string(i));
            ui.menuButtons[i].label.setFont(resources.font);
            ui.menuButtons[i].label.setCharacterSize(13);
            ui.menuButtons[i].label.setFillColor(sf::Color::White);
            SetTextRelativePosition(ui.menuButtons[i].label, 0.5f, 0.6f);
            ShiftTextPozition(ui.menuButtons[i].label, 0.f, 20.f * i);
        }

        ui.tint.setFillColor(sf::Color(0, 0, 0, 180));
        ui.tint.setSize(sf::Vector2f(LEVEL_WIDTH * CELL_SIZE, (LEVEL_HEIGHT + UI_HEIGHT) * CELL_SIZE));
    }

    void UpdateMenuUI(UI &ui, Menu &menu)
    {
        ui.menuLabel.setString(menu.label);
        SetTextRelativeOrigin(ui.menuLabel, 0.5f, 0.5f);
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

    void DrawMenuUI(UI &ui, Menu &menu, sf::RenderTexture &texture)
    {
        texture.draw(ui.tint);
        texture.draw(ui.menuLabel);
        for (int i = 0; i < menu.items.size(); ++i)
        {
            texture.draw(ui.menuButtons[i].label);
        }
    }

}