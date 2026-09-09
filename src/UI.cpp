#include "UI.h"
#include "GameMath.h"
#include <cmath>

namespace SnakeGame
{
    void InitUI(UI &ui, Resources &resources)
    {
        ui.hudBackground.setFillColor(COLOR_BASE);
        ui.hudBackground.setSize(sf::Vector2f(LEVEL_WIDTH * CELL_SIZE, 24.f));

        ui.menuLabel.setString("menuLabel");
        ui.menuLabel.setFont(resources.font);
        ui.menuLabel.setStyle(sf::Text::Bold);
        ui.menuLabel.setCharacterSize(48);
        ui.menuLabel.setFillColor(sf::Color::White);
        SetTextRelativePosition(ui.menuLabel, 0.5f, 0.1f);

        ui.menuButtons.clear();
        ui.menuButtons.resize(NUM_MENU_BUTTONS);
        for (size_t i = 0; i < ui.menuButtons.size(); ++i)
        {
            InitMenuButton(ui.menuButtons[i], resources);
            UpdateMenuBottonPosition(ui.menuButtons[i], 83 + (i * 21));
        }

        ui.tint.setFillColor(COLOR_TINT);
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
                UpdateMenuBottonText(ui.menuButtons[i], menu.items[i].label);
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
                ui.menuButtons[i].label.setFillColor(sf::Color::White);
            }
            else
            {
                ui.menuButtons[i].label.setFillColor(COLOR_TEXT);
            }
        };
    }

    void DrawMenuUI(UI &ui, Menu &menu, sf::RenderTexture &texture)
    {
        texture.draw(ui.tint);
        texture.draw(ui.menuLabel);
        for (int i = 0; i < menu.items.size(); ++i)
        {
            texture.draw(ui.menuButtons[i].sprite);
            texture.draw(ui.menuButtons[i].label);
        }
    }

    void DrawHud(UI &ui, sf::RenderTexture &texture)
    {
        texture.draw(ui.hudBackground);
    }

    void InitMenuButton(Button &button, Resources &resources)
    {
        button.label.setString("button");
        button.label.setFont(resources.font);
        button.label.setCharacterSize(16);
        button.label.setFillColor(COLOR_TEXT);
        button.sprite.setTexture(resources.button);

        sf::FloatRect spriteRect = button.sprite.getLocalBounds();
        sf::Vector2f origin = {std::round(spriteRect.width / 2), 0.f};
        button.sprite.setOrigin(origin);
    }

    void UpdateMenuBottonPosition(Button &button, int positionY)
    {
        sf::Vector2f position = {std::round(LEVEL_WIDTH * CELL_SIZE / 2), (float)positionY};
        button.sprite.setPosition(position);
        button.label.setPosition(position);
    }

    void UpdateMenuBottonText(Button &button, std::string text)
    {
        button.label.setString(text);
        sf::FloatRect textRect = button.label.getLocalBounds();
        sf::Vector2f origin = {std::round(textRect.width / 2), 4.f};
        button.label.setOrigin(origin);
    }

}