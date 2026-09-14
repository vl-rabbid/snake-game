#include "UI.h"
#include <cmath>

namespace SnakeGame
{
    void InitUI(UI &ui, Resources &resources)
    {
        ui.hud.setTexture(resources.hud);
        ui.hudLevelName.setTexture(resources.hudLevelName);
        ui.hudLevelName.setPosition({176.f, 4.f});
        ui.hudScore.setTexture(resources.hudScore);
        ui.hudScore.setPosition({2.f, 4.f});

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

        ui.menuLabelShadow.setString("menuLabel");
        ui.menuLabelShadow.setFont(resources.font);
        ui.menuLabelShadow.setStyle(sf::Text::Bold);
        ui.menuLabelShadow.setCharacterSize(48);
        ui.menuLabelShadow.setFillColor(COLOR_SHADOW);

        ui.menuButtons.clear();
        ui.menuButtons.resize(MAX_MENU_BUTTONS);
        for (int i = 0; i < ui.menuButtons.size(); ++i)
        {
            InitMenuButton(ui.menuButtons[i], resources);
        }

        ui.tint.setFillColor(COLOR_TINT);
        ui.tint.setSize(sf::Vector2f(LEVEL_WIDTH * CELL_SIZE, (LEVEL_HEIGHT + HUD_HEIGHT) * CELL_SIZE));

        ui.selectorMenu.topLeft.setTexture(resources.atlas);
        ui.selectorMenu.topLeft.setTextureRect(GetTextureRect(TextureID::SelectorTopLeft));
        ui.selectorMenu.topLeft.setOrigin({2.f, 3.f});
        ui.selectorMenu.topRight.setTexture(resources.atlas);
        ui.selectorMenu.topRight.setTextureRect(GetTextureRect(TextureID::SelectorTopRight));
        ui.selectorMenu.topRight.setOrigin({6.f, 3.f});
        ui.selectorMenu.bottomLeft.setTexture(resources.atlas);
        ui.selectorMenu.bottomLeft.setTextureRect(GetTextureRect(TextureID::SelectorBottomLeft));
        ui.selectorMenu.bottomLeft.setOrigin({2.f, 11.f});
        ui.selectorMenu.bottomRight.setTexture(resources.atlas);
        ui.selectorMenu.bottomRight.setTextureRect(GetTextureRect(TextureID::SelectorBottomRight));
        ui.selectorMenu.bottomRight.setOrigin({6.f, 11.f});

        ui.menuUp.setTexture(resources.atlas);
        ui.menuUp.setTextureRect(GetTextureRect(TextureID::Up));
        ui.menuUp.setOrigin({4.f, 8.f});
        ui.menuDown.setTexture(resources.atlas);
        ui.menuDown.setTextureRect(GetTextureRect(TextureID::Down));
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

        ui.sliderVertical.setTexture(resources.atlas);
        ui.sliderVertical.setTextureRect(GetTextureRect(TextureID::SliderVertical));
        ui.sliderVertical.setOrigin({3.f, 5.f});
        ui.sliderBarVertical.setFillColor(COLOR_TEXT);

        ui.selectorLevel.topLeft.setTexture(resources.atlas);
        ui.selectorLevel.topLeft.setTextureRect(GetTextureRect(TextureID::SelectorTopLeft));
        ui.selectorLevel.topLeft.setOrigin({2.f, 3.f});
        ui.selectorLevel.topRight.setTexture(resources.atlas);
        ui.selectorLevel.topRight.setTextureRect(GetTextureRect(TextureID::SelectorTopRight));
        ui.selectorLevel.topRight.setOrigin({6.f, 3.f});
        ui.selectorLevel.bottomLeft.setTexture(resources.atlas);
        ui.selectorLevel.bottomLeft.setTextureRect(GetTextureRect(TextureID::SelectorBottomLeft));
        ui.selectorLevel.bottomLeft.setOrigin({2.f, 11.f});
        ui.selectorLevel.bottomRight.setTexture(resources.atlas);
        ui.selectorLevel.bottomRight.setTextureRect(GetTextureRect(TextureID::SelectorBottomRight));
        ui.selectorLevel.bottomRight.setOrigin({6.f, 11.f});

        ui.levelButtons.clear();
        ui.levelButtons.resize(DISPLAYED_LEVEL_COUNT);
        for (int i = 0; i < ui.levelButtons.size(); ++i)
        {
            InitLevelButton(ui.levelButtons[i], resources, 9 + (i * 75));
        }
        SetSelectorTargetPosition(ui.selectorLevel, ui.levelButtons[0].spriteButton.getGlobalBounds());
        ApplySelectorTargetPosition(ui.selectorLevel);
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
        InitLevelButton(ui.leaderboardLevel, resources, 9);

        ui.inputMenu.setTexture(resources.inputMenu);
        ui.inputMenu.setOrigin({std::round(ui.inputMenu.getLocalBounds().width / 2), 0.f});
        ui.inputMenu.setPosition({std::round(LEVEL_WIDTH * CELL_SIZE / 2), 64.f});
        ui.inputField.setTexture(resources.inputField);
        ui.inputField.setOrigin({std::round(ui.inputField.getLocalBounds().width / 2), 0.f});
        ui.inputField.setPosition({std::round(LEVEL_WIDTH * CELL_SIZE / 2), 81.f});
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
        ApplySelectorTargetPosition(ui.selectorMenu);
        ui.sliderVertical.setPosition({ui.sliderBarVertical.getPosition().x, ui.sliderVerticalTargetPositionY});
    }

    void LoadMenuUIItems(UI &ui, Menu &menu)
    {
        for (int i = 0; i < menu.displayedItemAmount; i++)
        {
            if (i + menu.firstDisplayedItem < menu.items.size())
            {
                MenuItem &item = menu.items[i + menu.firstDisplayedItem];
                SetMenuBottonText(ui.menuButtons[i], item.label, item.enabled, item.pressed);
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

        sf::FloatRect itemRect = ui.menuButtons[menu.selected - menu.firstDisplayedItem].spriteEnabled.getGlobalBounds();
        if (!menu.items[menu.selected].enabled || menu.items[menu.selected].pressed)
            itemRect.top++;
        SetSelectorTargetPosition(ui.selectorMenu, itemRect);

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
                if (!menu.items[menu.firstDisplayedItem + i].enabled)
                    texture.draw(ui.menuButtons[i].spriteDisabled);
                else if (menu.items[menu.firstDisplayedItem + i].pressed)
                    texture.draw(ui.menuButtons[i].spritePressed);
                else
                    texture.draw(ui.menuButtons[i].spriteEnabled);

                texture.draw(ui.menuButtons[i].label);
            }
        }

        texture.draw(ui.selectorMenu.topLeft);
        texture.draw(ui.selectorMenu.topRight);
        texture.draw(ui.selectorMenu.bottomLeft);
        texture.draw(ui.selectorMenu.bottomRight);

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
                texture.draw(ui.levelButtons[i].spriteButton);
                texture.draw(ui.levelButtons[i].spriteLabel);
                texture.draw(ui.levelButtons[i].spritePreviewFrame);
                texture.draw(ui.levelButtons[i].label);
                texture.draw(ui.levelButtons[i].preview, ui.levelButtons[i].previewStates);
            }
        }

        texture.draw(ui.selectorLevel.topLeft);
        texture.draw(ui.selectorLevel.topRight);
        texture.draw(ui.selectorLevel.bottomLeft);
        texture.draw(ui.selectorLevel.bottomRight);

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
        button.spriteEnabled.setTexture(resources.buttonEnabled);
        button.spriteDisabled.setTexture(resources.buttonDisabled);
        button.spritePressed.setTexture(resources.buttonPressed);

        sf::FloatRect spriteRect = button.spriteEnabled.getLocalBounds();
        button.spriteEnabled.setOrigin({std::round(spriteRect.width / 2), 0.f});
        button.spriteDisabled.setOrigin({std::round(spriteRect.width / 2), -1.f});
        button.spritePressed.setOrigin({std::round(spriteRect.width / 2), -1.f});
    }

    void SetMenuBottonPosition(Button &button, int positionY)
    {
        sf::Vector2f position = {std::round(LEVEL_WIDTH * CELL_SIZE / 2), (float)positionY};
        button.spriteEnabled.setPosition(position);
        button.spriteDisabled.setPosition(position);
        button.spritePressed.setPosition(position);
        button.label.setPosition(position);
    }

    void SetMenuBottonText(Button &button, std::string text, bool enabled, bool pressed)
    {
        button.label.setString(text);
        if (!enabled || pressed)
            button.label.setOrigin({std::round(button.label.getLocalBounds().width / 2), 3.f});
        else
            button.label.setOrigin({std::round(button.label.getLocalBounds().width / 2), 4.f});
    }

    void SetMenuButtonsListPosition(UI &ui, int displayedAmount)
    {
        int positionY = 167;
        for (int i = displayedAmount - 1; i >= 0; --i)
        {
            positionY -= 21;
            SetMenuBottonPosition(ui.menuButtons[i], positionY);
        }
        ui.menuUp.setPosition({std::round(LEVEL_WIDTH * CELL_SIZE / 2), (float)positionY});
        ui.sliderBarVertical.setPosition({171.f, (float)(positionY + 2)});
        ui.sliderBarVertical.setSize(sf::Vector2f(2.f, 163.f - (float)(positionY + 2)));
    }

    void InitLevelButton(LevelButton &button, Resources &resources, int positionX)
    {
        button.label.setFont(resources.font);
        button.label.setCharacterSize(16);
        button.label.setFillColor(COLOR_TEXT);
        button.spriteLabel.setTexture(resources.hudLevelName);
        button.spriteButton.setTexture(resources.levelSelectButton);
        button.spritePreviewFrame.setTexture(resources.levelPreviewFrame);

        button.spriteButton.setPosition({(float)positionX, 31.f});
        button.spriteLabel.setPosition({(float)(positionX + 5), 37.f});
        button.label.setPosition({button.spriteLabel.getGlobalBounds().left + std::round(button.spriteLabel.getLocalBounds().width / 2), 37.f});
        SetLevelBottonText(button, "level");
        button.spritePreviewFrame.setPosition({(float)(positionX + 5), 57.f});
        button.previewStates = button.spritePreviewFrame.getTransform();
        button.previewStates.transform.translate(1.f, 1.f);
        button.previewStates.transform.scale(3.f, 3.f);
    }

    void SetLevelBottonText(LevelButton &button, std::string text)
    {
        button.label.setString(text);
        button.label.setOrigin({std::round(button.label.getLocalBounds().width / 2), 4.f});
    }

    void LoadLevelSelectUI(UI &ui, LevelManager &levelManager)
    {
        LoadLevelSelectUIItems(ui, levelManager);
        SetLevelSelectedItem(ui, levelManager);
        ApplySelectorTargetPosition(ui.selectorLevel);
        ui.sliderHorizontal.setPosition(ui.sliderBarHorizontal.getPosition());
    }

    void LoadLevelSelectUIItems(UI &ui, const LevelManager &levelManager)
    {
        for (int i = 0; i < ui.levelButtons.size(); i++)
        {
            if (i + levelManager.firstDisplayedItem < levelManager.levels.size())
            {
                SetLevelBottonText(ui.levelButtons[i], levelManager.levels[i + levelManager.firstDisplayedItem].name);
                ui.levelButtons[i].preview = GenerateLevelPreview(levelManager.levels[i + levelManager.firstDisplayedItem]);
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
        sf::FloatRect itemRect = ui.levelButtons[levelManager.selected - levelManager.firstDisplayedItem].spriteButton.getGlobalBounds();
        SetSelectorTargetPosition(ui.selectorLevel, itemRect);

        if (ui.levelButtons.size() < levelManager.levels.size())
        {
            sf::Vector2f sliderPosition = ui.sliderBarHorizontal.getPosition();
            sliderPosition.x += std::round(ui.sliderBarHorizontal.getSize().x * (float)(levelManager.selected / (float)(levelManager.levels.size() - 1)));
            ui.sliderHorizontalTargetPositionX = sliderPosition.x;
        }
    }

    void SetSelectorTargetPosition(Selector &selector, sf::FloatRect target)
    {
        selector.targetPosition[0] = {target.left, target.top};
        selector.targetPosition[1] = {target.left + target.width, target.top};
        selector.targetPosition[2] = {target.left, target.top + target.height};
        selector.targetPosition[3] = {target.left + target.width, target.top + target.height};
    }

    void ApplySelectorTargetPosition(Selector &selector)
    {
        for (int i = 0; i < 4; i++)
        {
            selector.currentPosition[i] = selector.targetPosition[i];
        }
        ApplySelectorCurrentPosition(selector);
    }

    void ApplySelectorCurrentPosition(Selector &selector)
    {
        selector.topLeft.setPosition({std::round(selector.currentPosition[0].x), std::round(selector.currentPosition[0].y)});
        selector.topRight.setPosition({std::round(selector.currentPosition[1].x), std::round(selector.currentPosition[1].y)});
        selector.bottomLeft.setPosition({std::round(selector.currentPosition[2].x), std::round(selector.currentPosition[2].y)});
        selector.bottomRight.setPosition({std::round(selector.currentPosition[3].x), std::round(selector.currentPosition[3].y)});
    }

    void UpdateSelector(Selector &selector, const float deltaTime, const float speed)
    {
        for (int i = 0; i < 4; i++)
        {
            sf::Vector2f delta = {(selector.targetPosition[i].x - selector.currentPosition[i].x), (selector.targetPosition[i].y - selector.currentPosition[i].y)};
            if (std::abs(delta.x) < 0.5f && std::abs(delta.y) < 0.5f)
                selector.currentPosition[i] = selector.targetPosition[i];
            else
                selector.currentPosition[i] += delta * speed * deltaTime;
        }

        ApplySelectorCurrentPosition(selector);
    }

    void UpdateMenuUI(UI &ui, const float deltaTime)
    {
        UpdateSelector(ui.selectorMenu, deltaTime, SELECT_SPEED);

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
        UpdateSelector(ui.selectorLevel, deltaTime, SELECT_SPEED);

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

        SetLevelBottonText(ui.leaderboardLevel, levelManager.levels[levelManager.selected].name);
        ui.leaderboardLevel.preview = GenerateLevelPreview(levelManager.levels[levelManager.selected]);
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

        texture.draw(ui.leaderboardLevel.spriteButton);
        texture.draw(ui.leaderboardLevel.spriteLabel);
        texture.draw(ui.leaderboardLevel.spritePreviewFrame);
        texture.draw(ui.leaderboardLevel.label);
        texture.draw(ui.leaderboardLevel.preview, ui.leaderboardLevel.previewStates);
    }

    void SetDelayUIText(UI &ui, std::string text)
    {
        SetTextRelativePosition(ui.menuLabel, 0.5f, 0.25f);
        ui.menuLabelShadow.setPosition({ui.menuLabel.getPosition().x + 2, ui.menuLabel.getPosition().y + 2});
        ui.menuLabelShadow.setString(text);
        SetTextRelativeOrigin(ui.menuLabelShadow, 0.5f, 0.5f);
        ui.menuLabel.setString(text);
        SetTextRelativeOrigin(ui.menuLabel, 0.5f, 0.5f);
    }

    void DrawDelayUI(UI &ui, sf::RenderTexture &texture)
    {
        texture.draw(ui.menuLabelShadow);
        texture.draw(ui.menuLabel);
    }
}