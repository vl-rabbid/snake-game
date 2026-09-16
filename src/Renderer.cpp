#include "Renderer.h"
#include <cmath>

namespace SnakeGame
{
    Renderer::Renderer()
    {
    }

    Renderer::~Renderer()
    {
        window.close();
    }

    sf::RenderTexture &Renderer::GetTexture()
    {
        return texture;
    }

    void Renderer::SetWindow(unsigned int renderWidth, unsigned int renderHeight, std::string windowTitle)
    {
        title = windowTitle;
        window.create(sf::VideoMode(renderWidth, renderHeight), windowTitle);
        window.setFramerateLimit(60);
        texture.create(renderWidth, renderHeight);
        texture.setSmooth(false);
        sprite.setTexture(texture.getTexture());
        sprite.setTextureRect(sf::IntRect(0, 0, renderWidth, renderHeight));
    }

    void Renderer::SetWindowScale(float scale)
    {
        sf::Vector2u renderSize = texture.getSize();
        window.create(sf::VideoMode(renderSize.x * scale, renderSize.y * scale), title);
        sprite.setScale(scale, scale);
    }

    bool Renderer::WindowPoolEvent(sf::Event &event)
    {
        return window.pollEvent(event);
    }

    void Renderer::Clear()
    {
        texture.clear();
    }

    void Renderer::Display()
    {
        texture.display();
        window.clear();
        window.draw(sprite);
        window.display();
    }
}
