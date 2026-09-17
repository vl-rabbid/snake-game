#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "GameMath.h"

namespace SnakeGame
{
    class Hud
    {
    public:
        Hud() = default;

        void Init(const Resources &resources);
        void Update(std::string levelName, unsigned int score);
        void Draw(sf::RenderTexture &texture);

    private:
        sf::Sprite background;
        sf::Sprite levelNameFrame;
        sf::Text levelNameText;
        sf::Sprite scoreFrame;
        sf::Text scoreText;
    };

}
