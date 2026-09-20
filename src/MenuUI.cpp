#include "MenuUI.h"
#include <cmath>

namespace SnakeGame
{
    void MenuUI::Init(const Resources &resources)
    {
        title.setString("title");
        title.setFont(resources.font);
        title.setStyle(sf::Text::Bold);
        title.setCharacterSize(48);
        title.setFillColor(sf::Color::White);
        SetTextRelativePosition(title, 0.5f, 0.1f);

        titleShadow.setString("title");
        titleShadow.setFont(resources.font);
        titleShadow.setStyle(sf::Text::Bold);
        titleShadow.setCharacterSize(48);
        titleShadow.setFillColor(COLOR_SHADOW);
        titleShadow.setPosition({title.getPosition().x + 2, title.getPosition().y + 2});

        windowTint.setFillColor(COLOR_TINT);
        windowTint.setSize(sf::Vector2f(RENDER_WIDTH, RENDER_HEIGHT));

        buttons.clear();
        buttons.resize(MAX_MENU_BUTTONS);
        for (auto &button : buttons)
            button.Init(resources);

        selector.Init(resources);

        subBackground.setTexture(resources.subMenu);
        subBackground.setOrigin({std::round(subBackground.getLocalBounds().width / 2), 0.f});
        subBackground.setPosition({static_cast<float>(std::round(RENDER_WIDTH / 2)), 64.f});
        subTitleFrame.setTexture(resources.subMenuTitle);
        subTitleFrame.setOrigin({std::round(subTitleFrame.getLocalBounds().width / 2), 0.f});
        subTitleFrame.setPosition({static_cast<float>(std::round(RENDER_WIDTH / 2)), 57.f});

        SetDefaultText(resources, subTitleText, "title");
        CenterTextOnSprite(subTitleText, subTitleFrame);

        SetSpriteAtlas(resources, arrowUp, TextureID::Up);
        SetSpriteAtlas(resources, arrowDown, TextureID::Down);
        arrowDown.setPosition({static_cast<float>(std::round(RENDER_WIDTH / 2)), 166.f});

        SetSpriteAtlas(resources, slider, TextureID::SliderVertical);
        sliderBar.setFillColor(COLOR_TEXT);

        inputBackground.setTexture(resources.inputMenu);
        inputBackground.setOrigin({std::round(inputBackground.getLocalBounds().width / 2), 0.f});
        inputBackground.setPosition({static_cast<float>(std::round(RENDER_WIDTH / 2)), 64.f});

        inputFieldFrame.setTexture(resources.inputField);
        inputFieldFrame.setOrigin({std::round(inputFieldFrame.getLocalBounds().width / 2), 0.f});
        inputFieldFrame.setPosition({static_cast<float>(std::round(RENDER_WIDTH / 2)), 81.f});

        SetDefaultText(resources, inputFieldText, "PLAYERNAME");
        inputFieldText.setFillColor(COLOR_INPUT_TEXT);
        inputFieldText.setPosition({inputFieldFrame.getGlobalBounds().left + 8.f, inputFieldFrame.getGlobalBounds().top - 5.f});
        inputMarker.setFillColor(COLOR_INPUT_TEXT);
        inputMarker.setSize(sf::Vector2f(1.f, 11.f));
    }

    void MenuUI::Load(const Menu &menu)
    {
        type = menu.GetType();
        displayedItemAmount = menu.GetDisplayedItemAmount();

        if (type == MenuType::FullMenu)
        {
            title.setString(menu.GetTitle());
            SetTextRelativeOrigin(title, 0.5f, 0.5f);
            titleShadow.setString(menu.GetTitle());
            SetTextRelativeOrigin(titleShadow, 0.5f, 0.5f);
        }
        else if (type == MenuType::SubMenu || type == MenuType::InputString)
        {
            subTitleText.setString(menu.GetTitle());
            CenterTextOnSprite(subTitleText, subTitleFrame);
        }
        ShiftButtonPosition();
        LoadButtons(menu);
        selector.ApplyTargetPosition();
        slider.setPosition({sliderBar.getPosition().x, sliderTargetPositionY});
    }

    void MenuUI::LoadButtons(const Menu &menu)
    {
        items = menu.GetItems();
        firstDisplayedItem = menu.GetFirstDisplayedItem();
        for (int i = 0; i < displayedItemAmount; i++)
        {
            if (i + firstDisplayedItem < items.size())
            {
                MenuItem &item = items[i + firstDisplayedItem];
                buttons[i].SetText(item.label, item.enabled, item.pressed);
            }
        }
        SetSelector(menu.GetSelected());
    }

    void MenuUI::SetSelector(int selected)
    {
        bool enabled = items[selected].enabled;
        bool pressed = items[selected].pressed;
        const sf::FloatRect itemRect = buttons[selected - firstDisplayedItem].GetSelectorBounds(enabled, pressed);
        selector.SetTargetPosition(itemRect);

        if (displayedItemAmount < items.size())
        {
            sf::Vector2f sliderPosition = sliderBar.getPosition();
            sliderPosition.y += std::round(sliderBar.getSize().y * static_cast<float>(selected / static_cast<float>(items.size() - 1)));
            sliderTargetPositionY = sliderPosition.y;
        }
    }

    void MenuUI::DrawWindowTint(sf::RenderTexture &texture) const
    {
        texture.draw(windowTint);
    }

    void MenuUI::Draw(sf::RenderTexture &texture) const
    {
        if (type == MenuType::FullMenu)
        {
            texture.draw(titleShadow);
            texture.draw(title);
        }
        else if (type == MenuType::SubMenu)
        {
            texture.draw(subBackground);
            texture.draw(subTitleFrame);
            texture.draw(subTitleText);
        }
        else if (type == MenuType::InputString)
        {
            texture.draw(inputBackground);
            texture.draw(subTitleFrame);
            texture.draw(subTitleText);
            texture.draw(inputFieldFrame);
            texture.draw(inputFieldText);
            if (inputMarkerVisible)
                texture.draw(inputMarker);
        }

        for (int i = 0; i < displayedItemAmount; ++i)
        {
            if (i < items.size())
            {
                bool enabled = items[firstDisplayedItem + i].enabled;
                bool pressed = items[firstDisplayedItem + i].pressed;
                buttons[i].Draw(texture, enabled, pressed);
            }
        }

        selector.Draw(texture);

        if (displayedItemAmount < items.size() && firstDisplayedItem + displayedItemAmount < items.size())
            texture.draw(arrowDown);
        if (firstDisplayedItem > 0)
            texture.draw(arrowUp);

        if (displayedItemAmount < items.size())
        {
            texture.draw(sliderBar);
            texture.draw(slider);
        }
    }

    void MenuUI::Update(const float deltaTime)
    {
        selector.Update(deltaTime);

        sf::Vector2f currentPosition = slider.getPosition();
        float delta = sliderTargetPositionY - currentPosition.y;
        if (std::abs(delta) < 0.5f)
            currentPosition.y = sliderTargetPositionY;
        else
            currentPosition.y += delta * SLIDER_SPEED * deltaTime;
        slider.setPosition(currentPosition);
    }

    void MenuUI::UpdateInputMarker(const float deltaTime)
    {
        static float timer = 0.f;
        timer += deltaTime;
        if (timer >= INPUT_MARKER_INTERVAL)
        {
            inputMarkerVisible = !inputMarkerVisible;
            timer -= INPUT_MARKER_INTERVAL;
        }
    }

    void MenuUI::SetImputLabel(const std::string &string)
    {
        inputFieldText.setString(string);
        inputMarker.setPosition({inputFieldText.getGlobalBounds().left + inputFieldText.getGlobalBounds().width + 1.f, inputFieldFrame.getGlobalBounds().top + 2.f});
    }

    void MenuUI::ShiftButtonPosition()
    {
        int positionY = 167;
        for (int i = displayedItemAmount - 1; i >= 0; --i)
        {
            positionY -= 21;
            buttons[i].SetPosition(positionY);
        }
        arrowUp.setPosition({static_cast<float>(std::round(RENDER_WIDTH / 2)), static_cast<float>(positionY)});
        sliderBar.setPosition({171.f, static_cast<float>(positionY + 2)});
        sliderBar.setSize(sf::Vector2f(2.f, 163.f - static_cast<float>(positionY + 2)));
    }
}