#include "Application/Renderer.h"

namespace SnakeGame
{
    Renderer::~Renderer()
    {
        window.close();
    }

    sf::RenderTexture &Renderer::GetTexture()
    {
        return texture;
    }

    void Renderer::SetWindow(unsigned int renderWidth, unsigned int renderHeight, float windowScale, const std::string &windowTitle)
    {
        title = windowTitle;
        window.create(sf::VideoMode(static_cast<unsigned int>(renderWidth * windowScale), static_cast<unsigned int>(renderHeight * windowScale)), windowTitle);
        window.setFramerateLimit(60);
        texture.create(renderWidth, renderHeight);
        texture.setSmooth(false);
        sprite.setTexture(texture.getTexture());
        sprite.setTextureRect(sf::IntRect(0, 0, renderWidth, renderHeight));
        sprite.setScale(windowScale, windowScale);
    }

    void Renderer::SetWindowScale(float scale)
    {
        sf::Vector2u renderSize = texture.getSize();
        window.create(sf::VideoMode(static_cast<unsigned int>(renderSize.x * scale), static_cast<unsigned int>(renderSize.y * scale)), title);
        sprite.setScale(scale, scale);
    }

    bool Renderer::WindowPollEvent(sf::Event &event)
    {
        return window.pollEvent(event);
    }

    void Renderer::Clear()
    {
        texture.clear();
        window.clear();
    }

    void Renderer::Display()
    {
        texture.display();
        window.draw(sprite);
        window.display();
    }
}
