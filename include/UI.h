#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Constants.h"
#include "Resources.h"
#include "LevelConfig.h"

namespace SnakeGame
{
    struct Button
    {
        sf::Sprite spriteEnabled;
        sf::Sprite spriteDisabled;
        sf::Sprite spritePressed;
        sf::Text label;
    };

    struct LevelButton
    {
        sf::Text label;
        sf::Sprite spriteLabel;
        sf::Sprite spriteButton;
        sf::Sprite spritePreviewFrame;
        sf::VertexArray preview;
        sf::RenderStates previewStates;
    };

    struct Selector
    {
        sf::Sprite topLeft;
        sf::Sprite topRight;
        sf::Sprite bottomLeft;
        sf::Sprite bottomRight;
    };

    struct UI
    {
        sf::Sprite hud;
        sf::Sprite hudLevelName;
        sf::Text hudLevelNameLabel;
        sf::Sprite hudScore;
        sf::Text hudScoreLabel;

        Selector selectorMenu;
        std::vector<Button> menuButtons;
        sf::Text menuLabel;
        sf::Text menuLabelShadow;
        sf::RectangleShape tint;

        sf::Sprite menuUp;
        sf::Sprite menuDown;
        sf::Sprite subMenu;
        sf::Sprite subMenuTitle;
        sf::Text subMenuLabel;
        sf::Sprite slider;
        sf::RectangleShape sliderBar;

        std::vector<LevelButton> levelButtons;
        Selector selectorLevel;
    };

    void InitUI(UI &ui, Resources &resources);
    void UpdateMenuUI(UI &ui, Menu &menu);
    void UpdateMenuSelectedItem(UI &ui, Menu &menu);
    void DrawUITint(UI &ui, sf::RenderTexture &texture);
    void DrawMenuUI(UI &ui, Menu &menu, sf::RenderTexture &texture);
    void DrawLevelSelect(UI &ui, sf::RenderTexture &texture);
    void UpdateHud(UI &ui, std::string levelName, int score);
    void DrawHud(UI &ui, sf::RenderTexture &texture);
    void InitMenuButton(Button &button, Resources &resources);
    void UpdateMenuBottonPosition(Button &button, int positionY);
    void UpdateMenuBottonText(Button &button, std::string text, bool enabled, bool pressed);
    void UpdateSelectorPosition(Selector &selector, sf::FloatRect target);
    void PositionMenuButtonsList(UI &ui, int displayedAmount);
    void InitLevelButton(LevelButton &button, Resources &resources, int positionX);
    void UpdateLevelBottonText(LevelButton &button, std::string text);
    void LoadLevelSelect(UI &ui, const LevelConfig &levelConfig);
}