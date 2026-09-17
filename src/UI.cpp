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

        ui.selectorLevel.Init(resources);

        ui.levelButtons.clear();
        ui.levelButtons.resize(DISPLAYED_LEVEL_COUNT);
        for (int i = 0; i < ui.levelButtons.size(); ++i)
        {
            ui.levelButtons[i].Init(resources, 9 + (i * 75));
        }
        ui.levelRight.setTexture(resources.atlas);
        ui.levelRight.setTextureRect(GetTextureRect(TextureID::Right));
        ui.levelRight.setOrigin({6.f, 4.f});
        ui.levelRight.setPosition({238.f, 67.f});
        ui.levelLeft.setTexture(resources.atlas);
        ui.levelLeft.setTextureRect(GetTextureRect(TextureID::Left));
        ui.levelLeft.setOrigin({0.f, 4.f});
        ui.levelLeft.setPosition({1.f, 67.f});

        ui.sliderHorizontal.setTexture(resources.atlas);
        ui.sliderHorizontal.setTextureRect(GetTextureRect(TextureID::SliderHorizontal));
        ui.sliderHorizontal.setOrigin({5.f, 3.f});
        ui.sliderBarHorizontal.setFillColor(COLOR_TEXT);
        ui.sliderBarHorizontal.setPosition({11.f, 111.f});
        ui.sliderBarHorizontal.setSize(sf::Vector2f(218.f, 2.f));

        ui.leaderboardFrame.setTexture(resources.leaderboardFrame);
        ui.leaderboardFrame.setPosition(93.f, 31.f);
        ui.leaderboardLabelFrame.setTexture(resources.leaderboardLabelFrame);
        ui.leaderboardLabelFrame.setPosition(112.f, 25.f);
        ui.leaderboardLabel.setString("Leaderboard");
        ui.leaderboardLabel.setFont(resources.font);
        ui.leaderboardLabel.setCharacterSize(16);
        ui.leaderboardLabel.setFillColor(COLOR_TEXT);
        ui.leaderboardLabel.setOrigin({std::round(ui.leaderboardLabel.getLocalBounds().width / 2), 0.f});
        ui.leaderboardLabel.setPosition({std::round(ui.leaderboardLabelFrame.getGlobalBounds().left + ui.leaderboardLabelFrame.getGlobalBounds().width / 2), 21.f});
        for (int i = 0; i < LEADERBOARD_DISPLAYED; i++)
        {
            ui.leaderboardEntry[i].setString(std::to_string(i + 1) + ".Entry...........10");
            ui.leaderboardEntry[i].setFont(resources.font);
            ui.leaderboardEntry[i].setCharacterSize(16);
            ui.leaderboardEntry[i].setFillColor(COLOR_TEXT);
            ui.leaderboardEntry[i].setPosition({100.f, 36.f + (14.f * i)});
        }
        ui.leaderboardRight.setTexture(resources.atlas);
        ui.leaderboardRight.setTextureRect(GetTextureRect(TextureID::Right));
        ui.leaderboardRight.setOrigin({6.f, 4.f});
        ui.leaderboardRight.setPosition({233.f, 74.f});
        ui.leaderboardLeft.setTexture(resources.atlas);
        ui.leaderboardLeft.setTextureRect(GetTextureRect(TextureID::Left));
        ui.leaderboardLeft.setOrigin({0.f, 4.f});
        ui.leaderboardLeft.setPosition({85.f, 74.f});
        ui.leaderboardLevel.Init(resources, 9);

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

    void DrawLevelSelect(UI &ui, const LevelManager &levelManager, sf::RenderTexture &texture)
    {

        for (int i = 0; i < ui.levelButtons.size(); ++i)
        {
            if (i < levelManager.levels.size())
            {
                ui.levelButtons[i].Draw(texture);
            }
        }

        ui.selectorLevel.Draw(texture);

        if (ui.levelButtons.size() < levelManager.levels.size() && levelManager.firstDisplayedItem + ui.levelButtons.size() < levelManager.levels.size())
        {
            texture.draw(ui.levelRight);
        }
        if (levelManager.firstDisplayedItem > 0)
        {
            texture.draw(ui.levelLeft);
        }

        if (ui.levelButtons.size() < levelManager.levels.size())
        {
            texture.draw(ui.sliderBarHorizontal);
            texture.draw(ui.sliderHorizontal);
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

    void LoadLevelSelectUI(UI &ui, LevelManager &levelManager)
    {
        LoadLevelSelectUIItems(ui, levelManager);
        SetLevelSelectedItem(ui, levelManager);
        ui.selectorLevel.ApplyTargetPosition();
        ui.sliderHorizontal.setPosition(ui.sliderBarHorizontal.getPosition());
    }

    void LoadLevelSelectUIItems(UI &ui, const LevelManager &levelManager)
    {
        for (int i = 0; i < ui.levelButtons.size(); i++)
        {
            if (i + levelManager.firstDisplayedItem < levelManager.levels.size())
            {
                ui.levelButtons[i].SetLevelName(levelManager.levels[i + levelManager.firstDisplayedItem].GetName());
                ui.levelButtons[i].SetLevelPreview(levelManager.levels[i + levelManager.firstDisplayedItem].GenerateLevelPreview());
            }
        }
    }

    void SetLevelSelectedItem(UI &ui, LevelManager &levelManager)
    {
        if (levelManager.selected >= levelManager.firstDisplayedItem + ui.levelButtons.size())
        {
            levelManager.firstDisplayedItem = levelManager.selected - ui.levelButtons.size() + 1;
            LoadLevelSelectUIItems(ui, levelManager);
        }
        else if (levelManager.selected < levelManager.firstDisplayedItem)
        {
            levelManager.firstDisplayedItem = levelManager.selected;
            LoadLevelSelectUIItems(ui, levelManager);
        }
        sf::FloatRect itemRect = ui.levelButtons[levelManager.selected - levelManager.firstDisplayedItem].GetSelectorBounds();
        ui.selectorLevel.SetTargetPosition(itemRect);

        if (ui.levelButtons.size() < levelManager.levels.size())
        {
            sf::Vector2f sliderPosition = ui.sliderBarHorizontal.getPosition();
            sliderPosition.x += std::round(ui.sliderBarHorizontal.getSize().x * (float)(levelManager.selected / (float)(levelManager.levels.size() - 1)));
            ui.sliderHorizontalTargetPositionX = sliderPosition.x;
        }
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

    void UpdateLevelSelectUI(UI &ui, const float deltaTime)
    {
        ui.selectorLevel.Update(deltaTime);

        sf::Vector2f currentPosition = ui.sliderHorizontal.getPosition();
        float delta = ui.sliderHorizontalTargetPositionX - currentPosition.x;
        if (std::abs(delta) < 0.5f)
            currentPosition.x = ui.sliderHorizontalTargetPositionX;
        else
            currentPosition.x += delta * SLIDER_SPEED * deltaTime;
        ui.sliderHorizontal.setPosition(currentPosition);
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

    void LoadLeaderboardUI(UI &ui, Leaderboard &leaderboard, LevelManager &levelManager)
    {
        for (int i = 0; i < LEADERBOARD_DISPLAYED; i++)
        {
            if (i + leaderboard.firstDisplayedItem < leaderboard.entries.size())
            {
                std::string text = std::to_string(i + leaderboard.firstDisplayedItem + 1) + ".";
                text += leaderboard.entries[i + leaderboard.firstDisplayedItem].playerName;
                std::string score = std::to_string(leaderboard.entries[i + leaderboard.firstDisplayedItem].score);
                int dotNumber = 20 - text.size() - score.size();
                for (int i = 0; i < dotNumber; i++)
                {
                    text += ".";
                }
                ui.leaderboardEntry[i].setString(text + score);
            }
        }
        ui.leaderboardLevel.SetLevelName(levelManager.levels[levelManager.selected].GetName());
        ui.leaderboardLevel.SetLevelPreview(levelManager.levels[levelManager.selected].GenerateLevelPreview());
    }

    void DrawLeaderboardUI(UI &ui, Leaderboard &leaderboard, sf::RenderTexture &texture)
    {
        texture.draw(ui.leaderboardFrame);
        texture.draw(ui.leaderboardLabelFrame);
        texture.draw(ui.leaderboardLabel);
        for (int i = 0; i < LEADERBOARD_DISPLAYED; i++)
        {
            if (i + leaderboard.firstDisplayedItem < leaderboard.entries.size())
            {
                texture.draw(ui.leaderboardEntry[i]);
            }
        }
        if (LEADERBOARD_DISPLAYED < leaderboard.entries.size() && leaderboard.firstDisplayedItem + LEADERBOARD_DISPLAYED < leaderboard.entries.size())
        {
            texture.draw(ui.leaderboardRight);
        }
        if (leaderboard.firstDisplayedItem > 0)
        {
            texture.draw(ui.leaderboardLeft);
        }

        ui.leaderboardLevel.Draw(texture);
    }
}