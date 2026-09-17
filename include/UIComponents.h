#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"

namespace SnakeGame
{
    class Button
    {
    public:
        void Init(const Resources &resources);
        void SetPosition(int positionY);
        void SetText(const std::string &string, bool enabled, bool pressed);
        void Draw(sf::RenderTexture &texture, bool enabled, bool pressed) const;
        sf::FloatRect GetSelectorBounds(bool enabled, bool pressed) const;

    private:
        sf::Sprite spriteEnabled;
        sf::Sprite spriteDisabled;
        sf::Sprite spritePressed;
        sf::Text text;
    };

    class LevelButton
    {
    public:
        void Init(const Resources &resources, int positionX);
        void SetLevelName(const std::string &string);
        void SetLevelPreview(const sf::VertexArray &preview);
        void Draw(sf::RenderTexture &texture) const;
        sf::FloatRect GetSelectorBounds() const;

    private:
        sf::Text levelNameText;
        sf::Sprite levelNameFrame;
        sf::Sprite background;
        sf::Sprite previewFrame;
        sf::VertexArray preview;
        sf::RenderStates previewStates;
    };

    class Selector
    {
    public:
        void Init(const Resources &resources);
        void SetTargetPosition(sf::FloatRect target);
        void ApplyTargetPosition();
        void Update(const float deltaTime);
        void Draw(sf::RenderTexture &texture) const;

    private:
        void ApplyCurrentPosition();

        sf::Sprite topLeft;
        sf::Sprite topRight;
        sf::Sprite bottomLeft;
        sf::Sprite bottomRight;
        sf::Vector2f currentPosition[4];
        sf::Vector2f targetPosition[4];
    };
}
