#include "Resources.h"
#include <cassert>
#include <string>

namespace SnakeGame
{
    void InitResources(Resources &resources)
    {
        assert(resources.atlas.loadFromFile(std::string(RESOURCES_PATH) + "/graphics/atlas.png"));
        assert(resources.background.loadFromFile(std::string(RESOURCES_PATH) + "/graphics/background.png"));
        assert(resources.font.loadFromFile(std::string(RESOURCES_PATH) + "/fonts/monogram.ttf"));

        resources.button = CreateNineSliceTexture(resources.atlas, GetTextureRect(TextureID::UIFrame1), 83, 19);
    }

    sf::IntRect GetTextureRect(TextureID id)
    {
        switch (id)
        {
        case TextureID::SnakeBodyUp:
            return sf::IntRect(0, 0, 12, 12);
            break;
        case TextureID::SnakeBodyDown:
            return sf::IntRect(12, 0, 12, 12);
            break;
        case TextureID::SnakeBodyLeft:
            return sf::IntRect(24, 0, 12, 12);
            break;
        case TextureID::SnakeBodyRight:
            return sf::IntRect(36, 0, 12, 12);
            break;

        case TextureID::SnakeHeadUp:
            return sf::IntRect(48, 0, 12, 12);
            break;
        case TextureID::SnakeHeadDown:
            return sf::IntRect(60, 0, 12, 12);
            break;
        case TextureID::SnakeHeadLeft:
            return sf::IntRect(72, 0, 12, 12);
            break;
        case TextureID::SnakeHeadRight:
            return sf::IntRect(84, 0, 12, 12);
            break;

        case TextureID::SnakeTailUp:
            return sf::IntRect(96, 0, 12, 12);
            break;
        case TextureID::SnakeTailDown:
            return sf::IntRect(108, 0, 12, 12);
            break;
        case TextureID::SnakeTailLeft:
            return sf::IntRect(120, 0, 12, 12);
            break;
        case TextureID::SnakeTailRight:
            return sf::IntRect(132, 0, 12, 12);
            break;

        case TextureID::SnakeMouthUp:
            return sf::IntRect(0, 12, 12, 12);
            break;
        case TextureID::SnakeMouthDown:
            return sf::IntRect(12, 12, 12, 12);
            break;
        case TextureID::SnakeMouthLeft:
            return sf::IntRect(24, 12, 12, 12);
            break;
        case TextureID::SnakeMouthRight:
            return sf::IntRect(36, 12, 12, 12);
            break;

        case TextureID::SnakeCornerUpRight:
            return sf::IntRect(48, 12, 12, 12);
            break;
        case TextureID::SnakeCornerUpLeft:
            return sf::IntRect(60, 12, 12, 12);
            break;
        case TextureID::SnakeCornerDownRight:
            return sf::IntRect(72, 12, 12, 12);
            break;
        case TextureID::SnakeCornerDownLeft:
            return sf::IntRect(84, 12, 12, 12);
            break;

        case TextureID::SnakeDeadUp:
            return sf::IntRect(96, 12, 12, 12);
            break;
        case TextureID::SnakeDeadDown:
            return sf::IntRect(108, 12, 12, 12);
            break;
        case TextureID::SnakeDeadLeft:
            return sf::IntRect(120, 12, 12, 12);
            break;
        case TextureID::SnakeDeadRight:
            return sf::IntRect(132, 12, 12, 12);
            break;

        case TextureID::Apple:
            return sf::IntRect(0, 24, 12, 12);
            break;

        case TextureID::UIFrame1:
            return sf::IntRect(0, 48, 12, 12);
            break;
        case TextureID::UIFrame2:
            return sf::IntRect(12, 48, 12, 12);
            break;
        case TextureID::UIFrame3:
            return sf::IntRect(24, 48, 12, 12);
            break;

        case TextureID::SelectorTopLeft:
            return sf::IntRect(36, 48, 12, 12);
            break;
        case TextureID::SelectorTopRight:
            return sf::IntRect(48, 48, 12, 12);
            break;
        case TextureID::SelectorBottomLeft:
            return sf::IntRect(60, 48, 12, 12);
            break;
        case TextureID::SelectorBottomRight:
            return sf::IntRect(72, 48, 12, 12);
            break;

        case TextureID::MenuUp:
            return sf::IntRect(96, 48, 12, 12);
            break;
        case TextureID::MenuDown:
            return sf::IntRect(108, 48, 12, 12);
            break;

        default:
            break;
        }
        return sf::IntRect(0, 0, 12, 12);
    }

    sf::Texture CreateNineSliceTexture(const sf::Texture &atlas, sf::IntRect rect, unsigned int width, unsigned int height)
    {
        const unsigned int borderLeft = 4;
        const unsigned int borderRight = 4;
        const unsigned int borderTop = 4;
        const unsigned int borderBottom = 6;
        unsigned int centralWidth = rect.width - borderLeft - borderRight;
        unsigned int centralHeight = rect.height - borderTop - borderBottom;

        sf::Texture resultTexture;
        sf::RenderTexture renderTexture;
        renderTexture.create(width, height);
        renderTexture.clear(sf::Color::Transparent);

        auto drawPart = [&](int sourceX, int sourceY, int sourceWidth, int sourceHight,
                            float destinationX, float destinationY, float destinationWidth, float destinationHight)
        {
            sf::Sprite sprite;
            sprite.setTexture(atlas);
            sprite.setTextureRect(sf::IntRect(rect.left + sourceX, rect.top + sourceY, sourceWidth, sourceHight));
            sprite.setPosition(destinationX, destinationY);
            sprite.setScale(destinationWidth / sourceWidth, destinationHight / sourceHight);
            renderTexture.draw(sprite);
        };

        unsigned int centralTargetWidth = width - borderLeft - borderRight;
        unsigned int centralTargetHeight = height - borderTop - borderBottom;

        // Top
        drawPart(0, 0, borderLeft, borderTop,
                 0, 0, borderLeft, borderTop);
        drawPart(borderLeft, 0, centralWidth, borderTop,
                 borderLeft, 0, centralTargetWidth, borderTop);
        drawPart(borderLeft + centralWidth, 0, borderRight, borderTop,
                 borderLeft + centralTargetWidth, 0, borderRight, borderTop);
        // Center
        drawPart(0, borderTop, borderLeft, centralHeight,
                 0, borderTop, borderLeft, centralTargetHeight);
        drawPart(borderLeft, borderTop, centralWidth, centralHeight,
                 borderLeft, borderTop, centralTargetWidth, centralTargetHeight);
        drawPart(borderLeft + centralWidth, borderTop, borderRight, centralHeight,
                 borderLeft + centralTargetWidth, borderTop, borderRight, centralTargetHeight);
        // Bottom
        drawPart(0, borderTop + centralHeight, borderLeft, borderBottom,
                 0, borderTop + centralTargetHeight, borderLeft, borderBottom);
        drawPart(borderLeft, borderTop + centralHeight, centralWidth, borderBottom,
                 borderLeft, borderTop + centralTargetHeight, centralTargetWidth, borderBottom);
        drawPart(borderLeft + centralWidth, borderTop + centralHeight, borderRight, borderBottom,
                 borderLeft + centralTargetWidth, borderTop + centralTargetHeight, borderRight, borderBottom);

        renderTexture.display();
        sf::Image image;
        image = renderTexture.getTexture().copyToImage();
        resultTexture.loadFromImage(image);
        resultTexture.setSmooth(false);
        return resultTexture;
    }
}