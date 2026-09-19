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
    class MenuUI
    {
    public:
        void Init(const Resources &resources);
        void Load(const Menu &menu);
        void LoadButtons(const Menu &menu);
        void SetSelector(int selected);
        void DrawWindowTint(sf::RenderTexture &texture) const;
        void Draw(sf::RenderTexture &texture) const;
        void Update(const float deltaTime);

        void UpdateInputMarker(const float deltaTime);
        void SetImputLabel(const std::string &string);

    private:
        void ShiftButtonPosition();

        MenuType type;
        int displayedItemAmount;
        int firstDisplayedItem;
        std::vector<MenuItem> items;

        sf::Text title;
        sf::Text titleShadow;
        sf::RectangleShape windowTint;
        std::vector<Button> buttons;
        Selector selector;

        sf::Sprite subBackground;
        sf::Sprite subTitleFrame;
        sf::Text subTitleText;

        sf::Sprite arrowUp;
        sf::Sprite arrowDown;
        sf::RectangleShape sliderBar;
        sf::Sprite slider;
        float sliderTargetPositionY;

        sf::Sprite inputBackground;
        sf::Sprite inputFieldFrame;
        sf::Text inputFieldText;
        sf::RectangleShape inputMarker;
        bool inputMarkerVisible = true;
    };
}