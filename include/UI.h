#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Constants.h"
#include "Resources.h"
#include "LevelManager.h"

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
        sf::Sprite sliderVertical;
        sf::RectangleShape sliderBarVertical;

        std::vector<LevelButton> levelButtons;
        Selector selectorLevel;
        sf::Sprite sliderHorizontal;
        sf::RectangleShape sliderBarHorizontal;
        sf::Sprite levelRight;
        sf::Sprite levelLeft;
    };

    void InitUI(UI &ui, Resources &resources);
    void UpdateMenuUI(UI &ui, Menu &menu);
    void UpdateMenuSelectedItem(UI &ui, Menu &menu);
    void DrawUITint(UI &ui, sf::RenderTexture &texture);
    void DrawMenuUI(UI &ui, Menu &menu, sf::RenderTexture &texture);
    void DrawLevelSelect(UI &ui, const LevelManager &levelManager, sf::RenderTexture &texture);
    void UpdateHud(UI &ui, std::string levelName, int score);
    void DrawHud(UI &ui, sf::RenderTexture &texture);
    void InitMenuButton(Button &button, Resources &resources);
    void UpdateMenuBottonPosition(Button &button, int positionY);
    void UpdateMenuBottonText(Button &button, std::string text, bool enabled, bool pressed);
    void UpdateSelectorPosition(Selector &selector, sf::FloatRect target);
    void PositionMenuButtonsList(UI &ui, int displayedAmount);
    void InitLevelButton(LevelButton &button, Resources &resources, int positionX);
    void UpdateLevelBottonText(LevelButton &button, std::string text);
    void LoadLevelSelectUI(UI &ui, const LevelManager &levelManager);
    void UpdateLevelSelectedItem(UI &ui, LevelManager &levelManager);
}