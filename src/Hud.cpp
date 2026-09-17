#include "Hud.h"
#include <cmath>

namespace SnakeGame
{
    void Hud::Init(Resources &resources)
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
    }

    void Hud::Update(std::string levelName, unsigned int score)
    {
        levelNameText.setString(levelName);
        CenterTextOnSprite(levelNameText, levelNameFrame);
        scoreText.setString("Score: " + std::to_string(score));
    }

    void Hud::Draw(sf::RenderTexture &texture)
    {
        texture.draw(background);
        texture.draw(levelNameFrame);
        texture.draw(levelNameText);
        texture.draw(scoreFrame);
        texture.draw(scoreText);
    }
}
