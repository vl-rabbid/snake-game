#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Constants.h"
#include "Resources.h"

namespace SnakeGame
{
    struct Button
    {
        sf::Text label;
    };

    struct UI
    {
        sf::RectangleShape hudBackground;

        std::vector<Button> menuButtons;
        sf::Text menuLabel;
        sf::RectangleShape tint;
    };

    void InitUI(UI &ui, Resources &resources);
    void UpdateMenuUI(UI &ui, Menu &menu);
    void UpdateSelectedItem(UI &ui, Menu &menu);
    void DrawMenuUI(UI &ui, Menu &menu, sf::RenderTexture &texture);
    void DrawHud(UI &ui, sf::RenderTexture &texture);
}