#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Constants.h"
#include "Resources.h"

namespace SnakeGame
{
    struct Button
    {
        sf::Sprite sprite;
        sf::Text label;
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
        sf::RectangleShape hudBackground;
        Selector selector;
        std::vector<Button> menuButtons;
        sf::Text menuLabel;
        sf::RectangleShape tint;

        sf::Sprite menuUp;
        sf::Sprite menuDown;
        sf::Sprite subMenu;
        sf::Sprite subMenuTitle;
        sf::Text subMenuLabel;
        sf::Sprite slider;
        sf::RectangleShape sliderBar;
    };

    void InitUI(UI &ui, Resources &resources);
    void UpdateMenuUI(UI &ui, Menu &menu);
    void UpdateMenuSelectedItem(UI &ui, Menu &menu);
    void DrawMenuUI(UI &ui, Menu &menu, sf::RenderTexture &texture);
    void DrawHud(UI &ui, sf::RenderTexture &texture);
    void InitMenuButton(Button &button, Resources &resources);
    void UpdateMenuBottonPosition(Button &button, int positionY);
    void UpdateMenuBottonText(Button &button, std::string text);
    void UpdateSelectorPosition(Selector &selector, sf::FloatRect target);
}