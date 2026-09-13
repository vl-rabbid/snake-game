#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Constants.h"
#include "Resources.h"
#include "LevelManager.h"
#include "Leaderboard.h"

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
        sf::Vector2f currentPosition[4];
        sf::Vector2f targetPosition[4];
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
        float sliderVerticalTargetPositionY;
        sf::RectangleShape sliderBarVertical;

        std::vector<LevelButton> levelButtons;
        Selector selectorLevel;
        sf::Sprite sliderHorizontal;
        float sliderHorizontalTargetPositionX;
        sf::RectangleShape sliderBarHorizontal;
        sf::Sprite levelRight;
        sf::Sprite levelLeft;

        sf::Sprite leaderboardFrame;
        sf::Sprite leaderboardLabelFrame;
        sf::Text leaderboardLabel;
        sf::Text leaderboardEntry[LEADERBOARD_DISPLAYED];
        sf::Sprite leaderboardRight;
        sf::Sprite leaderboardLeft;
    };

    void InitUI(UI &ui, Resources &resources);
    void LoadMenuUI(UI &ui, Menu &menu);
    void LoadMenuUIItems(UI &ui, Menu &menu);
    void SetMenuSelectedItem(UI &ui, Menu &menu);
    void DrawUITint(UI &ui, sf::RenderTexture &texture);
    void DrawMenuUI(UI &ui, Menu &menu, sf::RenderTexture &texture);
    void DrawLevelSelect(UI &ui, const LevelManager &levelManager, sf::RenderTexture &texture);
    void UpdateHud(UI &ui, std::string levelName, int score);
    void DrawHud(UI &ui, sf::RenderTexture &texture);
    void InitMenuButton(Button &button, Resources &resources);
    void SetMenuBottonPosition(Button &button, int positionY);
    void SetMenuBottonText(Button &button, std::string text, bool enabled, bool pressed);
    void SetMenuButtonsListPosition(UI &ui, int displayedAmount);
    void InitLevelButton(LevelButton &button, Resources &resources, int positionX);
    void SetLevelBottonText(LevelButton &button, std::string text);
    void LoadLevelSelectUI(UI &ui, LevelManager &levelManager);
    void LoadLevelSelectUIItems(UI &ui, const LevelManager &levelManager);
    void SetLevelSelectedItem(UI &ui, LevelManager &levelManager);
    void SetSelectorTargetPosition(Selector &selector, sf::FloatRect target);
    void ApplySelectorTargetPosition(Selector &selector);
    void ApplySelectorCurrentPosition(Selector &selector);
    void UpdateSelector(Selector &selector, const float deltaTime, const float speed);
    void UpdateMenuUI(UI &ui, const float deltaTime);
    void UpdateLevelSelectUI(UI &ui, const float deltaTime);
    void LoadLeaderboardUI(UI &ui, Leaderboard &leaderboard, LevelManager &levelManager);
    void DrawLeaderboardUI(UI &ui, Leaderboard &leaderboard, sf::RenderTexture &texture);
    void SetDelayUIText(UI &ui, std::string text);
    void DrawDelayUI(UI &ui, sf::RenderTexture &texture);
}