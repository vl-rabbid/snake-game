#pragma once
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
    class Renderer
    {
    public:
        ~Renderer();

        sf::RenderTexture &GetTexture();
        void SetWindow(unsigned int renderWidth, unsigned int renderHeight, float windowScale, const std::string &windowTitle);
        void SetWindowScale(float scale);
        bool WindowPollEvent(sf::Event &event);
        void Clear();
        void Display();

    private:
        std::string title;
        sf::RenderWindow window;
        sf::RenderTexture texture;
        sf::Sprite sprite;
    };
}
