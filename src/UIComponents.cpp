#include "UIComponents.h"
#include <cmath>

namespace SnakeGame
{

    void Button::Init(const Resources &resources)
    {
        SetDefaultText(resources, text, "button");
        spriteEnabled.setTexture(resources.buttonEnabled);
        spriteDisabled.setTexture(resources.buttonDisabled);
        spritePressed.setTexture(resources.buttonPressed);

        sf::FloatRect spriteRect = spriteEnabled.getLocalBounds();
        spriteEnabled.setOrigin({std::round(spriteRect.width / 2), 0.f});
        spriteDisabled.setOrigin({std::round(spriteRect.width / 2), -1.f});
        spritePressed.setOrigin({std::round(spriteRect.width / 2), -1.f});
    }

    void Button::SetPosition(int positionY)
    {
        sf::Vector2f position;
        position.x = static_cast<float>(std::round(LEVEL_WIDTH * CELL_SIZE / 2));
        position.y = static_cast<float>(positionY);
        spriteEnabled.setPosition(position);
        spriteDisabled.setPosition(position);
        spritePressed.setPosition(position);
        text.setPosition(position);
    }

    void Button::SetText(const std::string &string, bool enabled, bool pressed)
    {
        text.setString(string);
        if (!enabled || pressed)
            CenterTextOnSprite(text, spriteDisabled);
        else
            CenterTextOnSprite(text, spriteEnabled);
    }

    void Button::Draw(sf::RenderTexture &texture, bool enabled, bool pressed) const
    {
        if (!enabled)
            texture.draw(spriteDisabled);
        else if (pressed)
            texture.draw(spritePressed);
        else
            texture.draw(spriteEnabled);
        texture.draw(text);
    }

    sf::FloatRect Button::GetSelectorBounds(bool enabled, bool pressed) const
    {
        sf::FloatRect bounds = spriteEnabled.getGlobalBounds();
        if (!enabled || pressed)
            bounds.top++;
        return bounds;
    }

    void LevelButton::Init(const Resources &resources, int positionX)
    {
        SetDefaultText(resources, levelNameText, "level");
        levelNameFrame.setTexture(resources.hudLevelName);
        background.setTexture(resources.levelSelectButton);
        previewFrame.setTexture(resources.levelPreviewFrame);

        background.setPosition({static_cast<float>(positionX), 31.f});
        levelNameFrame.setPosition({static_cast<float>(positionX + 5), 37.f});
        previewFrame.setPosition({static_cast<float>(positionX + 5), 57.f});

        previewStates = previewFrame.getTransform();
        previewStates.transform.translate(1.f, 1.f);
        previewStates.transform.scale(3.f, 3.f);
    }

    void LevelButton::SetLevelName(const std::string &string)
    {
        levelNameText.setString(string);
        CenterTextOnSprite(levelNameText, levelNameFrame);
    }

    void LevelButton::SetLevelPreview(const sf::VertexArray &levelPreview)
    {
        preview = levelPreview;
    }

    void LevelButton::Draw(sf::RenderTexture &texture) const
    {
        texture.draw(background);
        texture.draw(levelNameFrame);
        texture.draw(levelNameText);
        texture.draw(previewFrame);
        texture.draw(preview, previewStates);
    }

    sf::FloatRect LevelButton::GetSelectorBounds() const
    {
        return background.getGlobalBounds();
    }

    void Selector::Init(const Resources &resources)
    {
        SetSpriteAtlas(resources, topLeft, TextureID::SelectorTopLeft);
        SetSpriteAtlas(resources, topRight, TextureID::SelectorTopRight);
        SetSpriteAtlas(resources, bottomLeft, TextureID::SelectorBottomLeft);
        SetSpriteAtlas(resources, bottomRight, TextureID::SelectorBottomRight);
    }

    void Selector::SetTargetPosition(sf::FloatRect target)
    {
        targetPosition[0] = {target.left, target.top};
        targetPosition[1] = {target.left + target.width, target.top};
        targetPosition[2] = {target.left, target.top + target.height};
        targetPosition[3] = {target.left + target.width, target.top + target.height};
    }

    void Selector::ApplyTargetPosition()
    {
        for (int i = 0; i < 4; i++)
            currentPosition[i] = targetPosition[i];
        ApplyCurrentPosition();
    }

    void Selector::ApplyCurrentPosition()
    {
        topLeft.setPosition({std::round(currentPosition[0].x), std::round(currentPosition[0].y)});
        topRight.setPosition({std::round(currentPosition[1].x), std::round(currentPosition[1].y)});
        bottomLeft.setPosition({std::round(currentPosition[2].x), std::round(currentPosition[2].y)});
        bottomRight.setPosition({std::round(currentPosition[3].x), std::round(currentPosition[3].y)});
    }

    void Selector::Update(const float deltaTime)
    {
        for (int i = 0; i < 4; i++)
        {
            sf::Vector2f delta = {(targetPosition[i].x - currentPosition[i].x), (targetPosition[i].y - currentPosition[i].y)};
            if (std::abs(delta.x) < 0.5f && std::abs(delta.y) < 0.5f)
                currentPosition[i] = targetPosition[i];
            else
                currentPosition[i] += delta * SELECTOR_SPEED * deltaTime;
        }
        ApplyCurrentPosition();
    }

    void Selector::Draw(sf::RenderTexture &texture) const
    {
        texture.draw(topLeft);
        texture.draw(topRight);
        texture.draw(bottomLeft);
        texture.draw(bottomRight);
    }
}