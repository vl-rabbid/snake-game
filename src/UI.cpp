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

        ui.selector.topLeft.setTexture(resources.atlas);
        ui.selector.topLeft.setTextureRect(GetTextureRect(TextureID::SelectorTopLeft));
        ui.selector.topLeft.setOrigin({2.f, 3.f});
        ui.selector.topRight.setTexture(resources.atlas);
        ui.selector.topRight.setTextureRect(GetTextureRect(TextureID::SelectorTopRight));
        ui.selector.topRight.setOrigin({6.f, 3.f});
        ui.selector.bottomLeft.setTexture(resources.atlas);
        ui.selector.bottomLeft.setTextureRect(GetTextureRect(TextureID::SelectorBottomLeft));
        ui.selector.bottomLeft.setOrigin({2.f, 11.f});
        ui.selector.bottomRight.setTexture(resources.atlas);
        ui.selector.bottomRight.setTextureRect(GetTextureRect(TextureID::SelectorBottomRight));
        ui.selector.bottomRight.setOrigin({6.f, 11.f});

        ui.menuUp.setTexture(resources.atlas);
        ui.menuUp.setTextureRect(GetTextureRect(TextureID::MenuUp));
        ui.menuUp.setOrigin({4.f, 0.f});
        ui.menuUp.setPosition({std::round(LEVEL_WIDTH * CELL_SIZE / 2), 74.f});
        ui.menuDown.setTexture(resources.atlas);
        ui.menuDown.setTextureRect(GetTextureRect(TextureID::MenuDown));
        ui.menuDown.setOrigin({4.f, 0.f});
        ui.menuDown.setPosition({std::round(LEVEL_WIDTH * CELL_SIZE / 2), 167.f});
    }

    void UpdateMenuUI(UI &ui, Menu &menu)
    {
        ui.menuLabel.setString(menu.label);
        SetTextRelativeOrigin(ui.menuLabel, 0.5f, 0.5f);
        for (int i = 0; i < ui.menuButtons.size(); i++)
        {
            if (i + menu.firstDisplayedItem < menu.items.size())
            {
                UpdateMenuBottonText(ui.menuButtons[i], menu.items[i + menu.firstDisplayedItem].label);
            }
        }
    }

    void UpdateMenuSelectedItem(UI &ui, Menu &menu)
    {
        if (menu.selected - menu.firstDisplayedItem >= NUM_MENU_BUTTONS)
        {
            menu.firstDisplayedItem = menu.selected - NUM_MENU_BUTTONS + 1;
            UpdateMenuUI(ui, menu);
        }
        else if ((menu.selected - menu.firstDisplayedItem < 0))
        {
            menu.firstDisplayedItem = menu.selected;
            UpdateMenuUI(ui, menu);
        }
        sf::FloatRect itemRect = ui.menuButtons[menu.selected - menu.firstDisplayedItem].sprite.getGlobalBounds();
        UpdateSelectorPosition(ui.selector, itemRect);
    }

    void DrawMenuUI(UI &ui, Menu &menu, sf::RenderTexture &texture)
    {
        texture.draw(ui.tint);
        texture.draw(ui.menuLabel);
        for (int i = 0; i < ui.menuButtons.size(); ++i)
        {
            if (i < menu.items.size())
            {
                texture.draw(ui.menuButtons[i].sprite);
                texture.draw(ui.menuButtons[i].label);
            }
        }
        texture.draw(ui.selector.topLeft);
        texture.draw(ui.selector.topRight);
        texture.draw(ui.selector.bottomLeft);
        texture.draw(ui.selector.bottomRight);

        if (ui.menuButtons.size() < menu.items.size() && menu.firstDisplayedItem + NUM_MENU_BUTTONS < menu.items.size())
        {
            texture.draw(ui.menuDown);
        }
        if (menu.firstDisplayedItem > 0)
        {
            texture.draw(ui.menuUp);
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

    void UpdateSelectorPosition(Selector &selector, sf::FloatRect target)
    {
        selector.topLeft.setPosition(target.left, target.top);
        selector.topRight.setPosition(target.left + target.width, target.top);
        selector.bottomLeft.setPosition(target.left, target.top + target.height);
        selector.bottomRight.setPosition(target.left + target.width, target.top + target.height);
    }

}