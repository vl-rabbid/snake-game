#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Constants.h"

namespace SnakeGame
{
    struct Button
    {
        sf::Text label;
    };

    struct UI
    {
        std::vector<Button> menuButtons;
        sf::Text menuLabel;
        sf::Font font;
        sf::RectangleShape tint;
    };

    void InitUI(UI &ui);
    void UpdateMenuUI(UI &ui, Menu &menu);
    void UpdateSelectedItem(UI &ui, Menu &menu);
    void DrawMenuUI(UI &ui, Menu &menu, sf::RenderWindow &window);
}