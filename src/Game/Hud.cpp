#include "Game/Hud.h"
#include <cmath>

namespace SnakeGame
{
    void Hud::Init(const Resources &resources)
    {
        background.setTexture(resources.hud);
        levelNameFrame.setTexture(resources.hudLevelName);
        levelNameFrame.setPosition({176.f, 4.f});
        scoreFrame.setTexture(resources.hudScore);
        scoreFrame.setPosition({2.f, 4.f});

        SetDefaultText(resources, levelNameText, "level");
        CenterTextOnSprite(levelNameText, levelNameFrame);

        SetDefaultText(resources, scoreText, "Score: ");
        scoreText.setPosition({8.f, 0.f});

        windowTint.setFillColor(COLOR_TINT);
        windowTint.setSize(sf::Vector2f(static_cast<float>(RENDER_WIDTH), static_cast<float>(RENDER_HEIGHT)));

        delayText.setString("delay");
        delayText.setFont(resources.font);
        delayText.setStyle(sf::Text::Bold);
        delayText.setCharacterSize(48);
        delayText.setFillColor(sf::Color::White);
        SetTextRelativePosition(delayText, 0.5f, 0.25f);

        delayTextShadow.setString("delay");
        delayTextShadow.setFont(resources.font);
        delayTextShadow.setStyle(sf::Text::Bold);
        delayTextShadow.setCharacterSize(48);
        delayTextShadow.setFillColor(COLOR_SHADOW);
        sf::Vector2f position = delayText.getPosition();
        position.x += 2.f;
        position.y += 2.f;
        delayTextShadow.setPosition(position);
    }

    void Hud::Update(std::string levelName, unsigned int score)
    {
        levelNameText.setString(levelName);
        CenterTextOnSprite(levelNameText, levelNameFrame);
        scoreText.setString("Score: " + std::to_string(score));
    }

    void Hud::Draw(sf::RenderTexture &texture) const
    {
        texture.draw(background);
        texture.draw(levelNameFrame);
        texture.draw(levelNameText);
        texture.draw(scoreFrame);
        texture.draw(scoreText);
    }

    void Hud::SetDelayText(const std::string &string)
    {
        delayText.setString(string);
        SetTextRelativeOrigin(delayText, 0.5f, 0.5f);
        delayTextShadow.setString(string);
        SetTextRelativeOrigin(delayTextShadow, 0.5f, 0.5f);
    }

    void Hud::DrawDelay(sf::RenderTexture &texture) const
    {
        texture.draw(windowTint);
        texture.draw(delayTextShadow);
        texture.draw(delayText);
    }
}
