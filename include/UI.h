#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Constants.h"
#include "Resources.h"
#include "LevelManager.h"
#include "Leaderboard.h"
#include "UIComponents.h"

namespace SnakeGame
{
    struct UI
    {
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

        sf::Sprite leaderboardFrame;
        sf::Sprite leaderboardLabelFrame;
        sf::Text leaderboardLabel;
        sf::Text leaderboardEntry[LEADERBOARD_DISPLAYED];
        sf::Sprite leaderboardRight;
        sf::Sprite leaderboardLeft;
        LevelButton leaderboardLevel;

        sf::Sprite inputMenu;
        sf::Sprite inputField;
        sf::Text inputLabel;
        sf::RectangleShape inputMarker;
        bool inputMarkerVisible = true;
    };

    void InitUI(UI &ui, Resources &resources);
    void LoadMenuUI(UI &ui, Menu &menu);
    void LoadMenuUIItems(UI &ui, Menu &menu);
    void SetMenuSelectedItem(UI &ui, Menu &menu);
    void DrawUITint(UI &ui, sf::RenderTexture &texture);
    void DrawMenuUI(UI &ui, Menu &menu, sf::RenderTexture &texture);
    void SetMenuButtonsListPosition(UI &ui, int displayedAmount);
    void UpdateMenuUI(UI &ui, const float deltaTime);
    void UpdateInputMarker(UI &ui, const float deltaTime);
    void SetInputLabel(UI &ui, std::string text);
    void LoadLeaderboardUI(UI &ui, Leaderboard &leaderboard, LevelManager &levelManager);
    void DrawLeaderboardUI(UI &ui, Leaderboard &leaderboard, sf::RenderTexture &texture);
}