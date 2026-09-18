#include "UI.h"
#include <cmath>

namespace SnakeGame
{
    void InitUI(UI &ui, Resources &resources)
    {
        ui.menuLabel.setString("menuLabel");
        ui.menuLabel.setFont(resources.font);
        ui.menuLabel.setStyle(sf::Text::Bold);
        ui.menuLabel.setCharacterSize(48);
        ui.menuLabel.setFillColor(sf::Color::White);

        ui.menuLabelShadow.setString("menuLabel");
        ui.menuLabelShadow.setFont(resources.font);
        ui.menuLabelShadow.setStyle(sf::Text::Bold);
        ui.menuLabelShadow.setCharacterSize(48);
        ui.menuLabelShadow.setFillColor(COLOR_SHADOW);

        ui.menuButtons.clear();
        ui.menuButtons.resize(MAX_MENU_BUTTONS);
        for (int i = 0; i < ui.menuButtons.size(); ++i)
        {
            ui.menuButtons[i].Init(resources);
        }

        ui.tint.setFillColor(COLOR_TINT);
        ui.tint.setSize(sf::Vector2f(LEVEL_WIDTH * CELL_SIZE, (LEVEL_HEIGHT + HUD_HEIGHT) * CELL_SIZE));

        ui.selectorMenu.Init(resources);

        ui.menuUp.setTexture(resources.atlas);
        ui.menuUp.setTextureRect(GetTextureRect(TextureID::Up));
        ui.menuUp.setOrigin({4.f, 8.f});
        ui.menuDown.setTexture(resources.atlas);
        ui.menuDown.setTextureRect(GetTextureRect(TextureID::Down));
        ui.menuDown.setOrigin({4.f, 0.f});
        ui.menuDown.setPosition({(float)std::round(LEVEL_WIDTH * CELL_SIZE / 2), 166.f});

        ui.subMenu.setTexture(resources.subMenu);
        ui.subMenu.setOrigin({std::round(ui.subMenu.getLocalBounds().width / 2), 0.f});
        ui.subMenu.setPosition({(float)std::round(LEVEL_WIDTH * CELL_SIZE / 2), 64.f});
        ui.subMenuTitle.setTexture(resources.subMenuTitle);
        ui.subMenuTitle.setOrigin({std::round(ui.subMenuTitle.getLocalBounds().width / 2), 0.f});
        ui.subMenuTitle.setPosition({(float)std::round(LEVEL_WIDTH * CELL_SIZE / 2), 57.f});

        ui.subMenuLabel.setString("subMenu");
        ui.subMenuLabel.setFont(resources.font);
        ui.subMenuLabel.setCharacterSize(16);
        ui.subMenuLabel.setFillColor(COLOR_TEXT);
        ui.subMenuLabel.setOrigin({std::round(ui.subMenuLabel.getLocalBounds().width / 2), 0.f});
        ui.subMenuLabel.setPosition({(float)std::round(LEVEL_WIDTH * CELL_SIZE / 2), 53.f});

        ui.sliderVertical.setTexture(resources.atlas);
        ui.sliderVertical.setTextureRect(GetTextureRect(TextureID::SliderVertical));
        ui.sliderVertical.setOrigin({3.f, 5.f});
        ui.sliderBarVertical.setFillColor(COLOR_TEXT);

        ui.inputMenu.setTexture(resources.inputMenu);
        ui.inputMenu.setOrigin({std::round(ui.inputMenu.getLocalBounds().width / 2), 0.f});
        ui.inputMenu.setPosition({(float)std::round(LEVEL_WIDTH * CELL_SIZE / 2), 64.f});
        ui.inputField.setTexture(resources.inputField);
        ui.inputField.setOrigin({std::round(ui.inputField.getLocalBounds().width / 2), 0.f});
        ui.inputField.setPosition({(float)std::round(LEVEL_WIDTH * CELL_SIZE / 2), 81.f});
        ui.inputLabel.setString("PLAYERNAME");
        ui.inputLabel.setFont(resources.font);
        ui.inputLabel.setCharacterSize(16);
        ui.inputLabel.setFillColor(COLOR_INPUT_TEXT);
        ui.inputLabel.setPosition({ui.inputField.getGlobalBounds().left + 8.f, ui.inputField.getGlobalBounds().top - 5.f});
        ui.inputMarker.setFillColor(COLOR_INPUT_TEXT);
        ui.inputMarker.setSize(sf::Vector2f(1.f, 11.f));
        ui.inputMarker.setPosition({ui.inputLabel.getGlobalBounds().left + ui.inputLabel.getGlobalBounds().width + 1.f, ui.inputField.getGlobalBounds().top + 2.f});
    }

    void LoadMenuUI(UI &ui, Menu &menu)
    {
        SetTextRelativePosition(ui.menuLabel, 0.5f, 0.1f);
        ui.menuLabelShadow.setPosition({ui.menuLabel.getPosition().x + 2, ui.menuLabel.getPosition().y + 2});
        if (menu.type == MenuType::FullMenu)
        {
            ui.menuLabel.setString(menu.label);
            SetTextRelativeOrigin(ui.menuLabel, 0.5f, 0.5f);
            ui.menuLabelShadow.setString(menu.label);
            SetTextRelativeOrigin(ui.menuLabelShadow, 0.5f, 0.5f);
        }
        else if (menu.type == MenuType::SubMenu || menu.type == MenuType::InputString)
        {
            ui.subMenuLabel.setString(menu.label);
            ui.subMenuLabel.setOrigin({std::round(ui.subMenuLabel.getLocalBounds().width / 2), 0.f});
        }

        SetMenuButtonsListPosition(ui, menu.displayedItemAmount);
        LoadMenuUIItems(ui, menu);
        ui.selectorMenu.ApplyTargetPosition();
        ui.sliderVertical.setPosition({ui.sliderBarVertical.getPosition().x, ui.sliderVerticalTargetPositionY});
    }

    void LoadMenuUIItems(UI &ui, Menu &menu)
    {
        for (int i = 0; i < menu.displayedItemAmount; i++)
        {
            if (i + menu.firstDisplayedItem < menu.items.size())
            {
                MenuItem &item = menu.items[i + menu.firstDisplayedItem];
                ui.menuButtons[i].SetText(item.label, item.enabled, item.pressed);
            }
        }
        SetMenuSelectedItem(ui, menu);
    }

    void SetMenuSelectedItem(UI &ui, Menu &menu)
    {
        if (menu.selected >= menu.firstDisplayedItem + menu.displayedItemAmount)
        {
            menu.firstDisplayedItem = menu.selected - menu.displayedItemAmount + 1;
            LoadMenuUIItems(ui, menu);
        }
        else if ((menu.selected < menu.firstDisplayedItem))
        {
            menu.firstDisplayedItem = menu.selected;
            LoadMenuUIItems(ui, menu);
        }

        bool enabled = menu.items[menu.selected].enabled;
        bool pressed = menu.items[menu.selected].pressed;
        const sf::FloatRect itemRect = ui.menuButtons[menu.selected - menu.firstDisplayedItem].GetSelectorBounds(enabled, pressed);
        ui.selectorMenu.SetTargetPosition(itemRect);

        if (menu.displayedItemAmount < menu.items.size())
        {
            sf::Vector2f sliderPosition = ui.sliderBarVertical.getPosition();
            sliderPosition.y += std::round(ui.sliderBarVertical.getSize().y * (float)(menu.selected / (float)(menu.items.size() - 1)));
            ui.sliderVerticalTargetPositionY = sliderPosition.y;
        }
    }

    void DrawUITint(UI &ui, sf::RenderTexture &texture)
    {
        texture.draw(ui.tint);
    }

    void DrawMenuUI(UI &ui, Menu &menu, sf::RenderTexture &texture)
    {
        if (menu.type == MenuType::FullMenu)
        {
            texture.draw(ui.menuLabelShadow);
            texture.draw(ui.menuLabel);
        }
        else if (menu.type == MenuType::SubMenu)
        {
            texture.draw(ui.subMenu);
            texture.draw(ui.subMenuTitle);
            texture.draw(ui.subMenuLabel);
        }
        else if (menu.type == MenuType::InputString)
        {
            texture.draw(ui.inputMenu);
            texture.draw(ui.subMenuTitle);
            texture.draw(ui.subMenuLabel);
            texture.draw(ui.inputField);
            texture.draw(ui.inputLabel);
            if (ui.inputMarkerVisible)
            {
                texture.draw(ui.inputMarker);
            }
        }

        for (int i = 0; i < menu.displayedItemAmount; ++i)
        {
            if (i < menu.items.size())
            {
                bool enabled = menu.items[menu.firstDisplayedItem + i].enabled;
                bool pressed = menu.items[menu.firstDisplayedItem + i].pressed;
                ui.menuButtons[i].Draw(texture, enabled, pressed);
            }
        }

        ui.selectorMenu.Draw(texture);

        if (menu.displayedItemAmount < menu.items.size() && menu.firstDisplayedItem + menu.displayedItemAmount < menu.items.size())
        {
            texture.draw(ui.menuDown);
        }
        if (menu.firstDisplayedItem > 0)
        {
            texture.draw(ui.menuUp);
        }

        if (menu.displayedItemAmount < menu.items.size())
        {
            texture.draw(ui.sliderBarVertical);
            texture.draw(ui.sliderVertical);
        }
    }

    void SetMenuButtonsListPosition(UI &ui, int displayedAmount)
    {
        int positionY = 167;
        for (int i = displayedAmount - 1; i >= 0; --i)
        {
            positionY -= 21;
            ui.menuButtons[i].SetPosition(positionY);
        }
        ui.menuUp.setPosition({(float)std::round(LEVEL_WIDTH * CELL_SIZE / 2), (float)positionY});
        ui.sliderBarVertical.setPosition({171.f, (float)(positionY + 2)});
        ui.sliderBarVertical.setSize(sf::Vector2f(2.f, 163.f - (float)(positionY + 2)));
    }

    void UpdateMenuUI(UI &ui, const float deltaTime)
    {
        ui.selectorMenu.Update(deltaTime);

        sf::Vector2f currentPosition = ui.sliderVertical.getPosition();
        float delta = ui.sliderVerticalTargetPositionY - currentPosition.y;
        if (std::abs(delta) < 0.5f)
            currentPosition.y = ui.sliderVerticalTargetPositionY;
        else
            currentPosition.y += delta * SLIDER_SPEED * deltaTime;
        ui.sliderVertical.setPosition(currentPosition);
    }

    void UpdateInputMarker(UI &ui, const float deltaTime)
    {
        static float timer = 0.f;
        timer += deltaTime;
        if (timer >= INPUT_MARKER_INTERVAL)
        {
            ui.inputMarkerVisible = !ui.inputMarkerVisible;
            timer -= INPUT_MARKER_INTERVAL;
        }
    }

    void SetInputLabel(UI &ui, std::string text)
    {
        ui.inputLabel.setString(text);
        ui.inputMarker.setPosition({ui.inputLabel.getGlobalBounds().left + ui.inputLabel.getGlobalBounds().width + 1.f, ui.inputField.getGlobalBounds().top + 2.f});
    }
}