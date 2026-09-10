#include "UI.h"
#include "GameMath.h"
#include <cmath>

namespace SnakeGame
{
    void InitUI(UI &ui, Resources &resources)
    {
        ui.hud.setTexture(resources.hud);
        ui.hudLevelName.setTexture(resources.hudLevelName);
        ui.hudLevelName.setPosition({163.f, 3.f});
        ui.hudScore.setTexture(resources.hudScore);
        ui.hudScore.setPosition({2.f, 3.f});

        ui.hudLevelNameLabel.setString("level");
        ui.hudLevelNameLabel.setFont(resources.font);
        ui.hudLevelNameLabel.setCharacterSize(16);
        ui.hudLevelNameLabel.setFillColor(COLOR_TEXT);
        ui.hudLevelNameLabel.setOrigin({std::round(ui.hudLevelNameLabel.getLocalBounds().width / 2), 0.f});
        ui.hudLevelNameLabel.setPosition({ui.hudLevelName.getGlobalBounds().left + std::round(ui.hudLevelName.getGlobalBounds().width / 2), 0.f});

        ui.hudScoreLabel.setString("Score: ");
        ui.hudScoreLabel.setFont(resources.font);
        ui.hudScoreLabel.setCharacterSize(16);
        ui.hudScoreLabel.setFillColor(COLOR_TEXT);
        ui.hudScoreLabel.setPosition({8.f, 0.f});

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
        ui.tint.setSize(sf::Vector2f(LEVEL_WIDTH * CELL_SIZE, (LEVEL_HEIGHT + HUD_HEIGHT) * CELL_SIZE));

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
        ui.menuUp.setPosition({std::round(LEVEL_WIDTH * CELL_SIZE / 2), 75.f});
        ui.menuDown.setTexture(resources.atlas);
        ui.menuDown.setTextureRect(GetTextureRect(TextureID::MenuDown));
        ui.menuDown.setOrigin({4.f, 0.f});
        ui.menuDown.setPosition({std::round(LEVEL_WIDTH * CELL_SIZE / 2), 166.f});

        ui.subMenu.setTexture(resources.subMenu);
        ui.subMenu.setOrigin({std::round(ui.subMenu.getLocalBounds().width / 2), 0.f});
        ui.subMenu.setPosition({std::round(LEVEL_WIDTH * CELL_SIZE / 2), 64.f});
        ui.subMenuTitle.setTexture(resources.subMenuTitle);
        ui.subMenuTitle.setOrigin({std::round(ui.subMenuTitle.getLocalBounds().width / 2), 0.f});
        ui.subMenuTitle.setPosition({std::round(LEVEL_WIDTH * CELL_SIZE / 2), 57.f});

        ui.subMenuLabel.setString("subMenu");
        ui.subMenuLabel.setFont(resources.font);
        ui.subMenuLabel.setCharacterSize(16);
        ui.subMenuLabel.setFillColor(COLOR_TEXT);
        ui.subMenuLabel.setOrigin({std::round(ui.subMenuLabel.getLocalBounds().width / 2), 0.f});
        ui.subMenuLabel.setPosition({std::round(LEVEL_WIDTH * CELL_SIZE / 2), 53.f});

        ui.slider.setTexture(resources.atlas);
        ui.slider.setTextureRect(GetTextureRect(TextureID::Slider));
        ui.slider.setOrigin({3.f, 5.f});

        ui.sliderBar.setFillColor(COLOR_TEXT);
        ui.sliderBar.setSize(sf::Vector2f(2.f, 78.f));
        ui.sliderBar.setPosition({171.f, 85.f});
    }

    void UpdateMenuUI(UI &ui, Menu &menu)
    {
        if (menu.type == MenuType::FullMenu)
        {
            ui.menuLabel.setString(menu.label);
            SetTextRelativeOrigin(ui.menuLabel, 0.5f, 0.5f);
        }
        else if (menu.type == MenuType::SubMenu)
        {
            ui.subMenuLabel.setString(menu.label);
            ui.subMenuLabel.setOrigin({std::round(ui.subMenuLabel.getLocalBounds().width / 2), 0.f});
        }

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

        if (ui.menuButtons.size() < menu.items.size())
        {
            sf::Vector2f sliderPosition = ui.sliderBar.getPosition();
            sliderPosition.y += std::round(ui.sliderBar.getSize().y * (float)(menu.selected / (float)(menu.items.size() - 1)));
            ui.slider.setPosition(sliderPosition);
        }
    }

    void DrawMenuUI(UI &ui, Menu &menu, sf::RenderTexture &texture)
    {
        texture.draw(ui.tint);
        texture.draw(ui.menuLabel);
        if (menu.type == MenuType::SubMenu)
        {
            texture.draw(ui.tint);
            texture.draw(ui.subMenu);
            texture.draw(ui.subMenuTitle);
            texture.draw(ui.subMenuLabel);
        }

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

        if (ui.menuButtons.size() < menu.items.size())
        {
            texture.draw(ui.sliderBar);
            texture.draw(ui.slider);
        }
    }

    void UpdateHud(UI &ui, std::string levelName, int score)
    {
        ui.hudLevelNameLabel.setString(levelName);
        ui.hudLevelNameLabel.setOrigin({std::round(ui.hudLevelNameLabel.getLocalBounds().width / 2), 0.f});

        ui.hudScoreLabel.setString("Score: " + std::to_string(score));
    }

    void DrawHud(UI &ui, sf::RenderTexture &texture)
    {
        texture.draw(ui.hud);
        texture.draw(ui.hudLevelName);
        texture.draw(ui.hudScore);
        texture.draw(ui.hudLevelNameLabel);
        texture.draw(ui.hudScoreLabel);
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