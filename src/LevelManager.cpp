#include "LevelManager.h"
#include <fstream>
#include <filesystem>
#include <cmath>

namespace SnakeGame
{
    void LevelManager::Init(const Resources &resources)
    {
        ui.selector.Init(resources);

        ui.buttons.clear();
        ui.buttons.resize(DISPLAYED_LEVEL_COUNT);
        for (int i = 0; i < ui.buttons.size(); ++i)
        {
            ui.buttons[i].Init(resources, 9 + (i * 75));
        }
        SetSpriteAtlas(resources, ui.arrowRight, TextureID::Right);
        ui.arrowRight.setPosition({238.f, 67.f});
        SetSpriteAtlas(resources, ui.arrowLeft, TextureID::Left);
        ui.arrowLeft.setPosition({1.f, 67.f});
        SetSpriteAtlas(resources, ui.slider, TextureID::SliderHorizontal);
        ui.sliderBar.setFillColor(COLOR_TEXT);
        ui.sliderBar.setPosition({11.f, 111.f});
        ui.sliderBar.setSize(sf::Vector2f(218.f, 2.f));
    }

    void LevelManager::Update(const float deltaTime)
    {
        ui.selector.Update(deltaTime);

        sf::Vector2f currentPosition = ui.slider.getPosition();
        float delta = ui.sliderTargetPositionX - currentPosition.x;
        if (std::abs(delta) < 0.5f)
            currentPosition.x = ui.sliderTargetPositionX;
        else
            currentPosition.x += delta * SLIDER_SPEED * deltaTime;
        ui.slider.setPosition(currentPosition);
    }

    void LevelManager::Draw(sf::RenderTexture &texture) const
    {
        for (int i = 0; i < ui.buttons.size(); ++i)
            if (i < levels.size())
                ui.buttons[i].Draw(texture);

        ui.selector.Draw(texture);

        if (ui.buttons.size() < levels.size() && firstDisplayedItem + ui.buttons.size() < levels.size())
            texture.draw(ui.arrowRight);
        if (firstDisplayedItem > 0)
            texture.draw(ui.arrowLeft);
        if (ui.buttons.size() < levels.size())
        {
            texture.draw(ui.sliderBar);
            texture.draw(ui.slider);
        }
    }

    void LevelManager::HandleInput(const sf::Event &event)
    {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
        {
            int previousItem = selected;
            selected -= 1;
            if (selected < 0)
                selected = levels.size() - 1;

            SetSelector();
            // if (previousItem != selected)
            // {
            //     PlaySound(game, game.soundFX, game.resources.uiMoveHorizontal);
            // }
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
        {
            int previousItem = selected;
            selected += 1;
            if (selected > levels.size() - 1)
            {
                selected = 0;
            }
            SetSelector();
            // if (previousItem != selected)
            // {
            //     PlaySound(game, game.soundFX, game.resources.uiMoveHorizontal);
            // }
        }
    }

    void LevelManager::LoadFromFiles()
    {
        firstDisplayedItem = 0;
        selected = 0;
        levels.clear();

        const std::filesystem::path levelsPath = std::filesystem::path(RESOURCES_PATH) / "levels";

        if (std::filesystem::exists(levelsPath) && std::filesystem::is_directory(levelsPath))
            for (const auto &entry : std::filesystem::directory_iterator(levelsPath))
                if (entry.is_regular_file() && entry.path().extension() == ".lvl")
                {
                    LevelConfig level;
                    level.LoadFromFile(entry.path().string());
                    levels.push_back(level);
                }

        if (levels.size() == 0)
        {
            LevelConfig level;
            level.SetEmpty();
            level.UpdatePreviewCells();
            levels.push_back(level);
        }
        LoadUI();
    }

    const LevelConfig &LevelManager::GetSelectedLevelConfig() const
    {
        return levels[selected];
    }

    void LevelManager::LoadUI()
    {
        LoadUIButtons();
        SetSelector();
        ui.selector.ApplyTargetPosition();
        ui.slider.setPosition(ui.sliderBar.getPosition());
    }

    void LevelManager::LoadUIButtons()
    {
        for (int i = 0; i < ui.buttons.size(); i++)
        {
            if (i + firstDisplayedItem < levels.size())
            {
                ui.buttons[i].SetLevelName(levels[i + firstDisplayedItem].GetName());
                ui.buttons[i].SetLevelPreview(levels[i + firstDisplayedItem].GenerateLevelPreview());
            }
        }
    }

    void LevelManager::SetSelector()
    {
        if (selected >= firstDisplayedItem + ui.buttons.size())
        {
            firstDisplayedItem = selected - ui.buttons.size() + 1;
            LoadUIButtons();
        }
        else if (selected < firstDisplayedItem)
        {
            firstDisplayedItem = selected;
            LoadUIButtons();
        }
        sf::FloatRect itemRect = ui.buttons[selected - firstDisplayedItem].GetSelectorBounds();
        ui.selector.SetTargetPosition(itemRect);

        if (ui.buttons.size() < levels.size())
        {
            sf::Vector2f sliderPosition = ui.sliderBar.getPosition();
            sliderPosition.x += std::round(ui.sliderBar.getSize().x * static_cast<float>(selected / static_cast<float>(levels.size() - 1)));
            ui.sliderTargetPositionX = sliderPosition.x;
        }
    }
}