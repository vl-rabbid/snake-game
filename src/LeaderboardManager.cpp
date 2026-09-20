#include "LeaderboardManager.h"

namespace SnakeGame
{
    void LeaderboardManager::Init(const Resources &resources)
    {
        ui.background.setTexture(resources.leaderboardFrame);
        ui.background.setPosition(93.f, 31.f);
        ui.titleFrame.setTexture(resources.leaderboardLabelFrame);
        ui.titleFrame.setPosition(112.f, 25.f);

        SetDefaultText(resources, ui.title, "Leaderboard");
        CenterTextOnSprite(ui.title, ui.titleFrame);
        for (int i = 0; i < LEADERBOARD_DISPLAYED; i++)
        {
            SetDefaultText(resources, ui.entry[i], "Entry");
            ui.entry[i].setPosition({100.f, 36.f + (14.f * i)});
        }

        SetSpriteAtlas(resources, ui.arrowRight, TextureID::Right);
        ui.arrowRight.setPosition({233.f, 74.f});
        SetSpriteAtlas(resources, ui.arrowLeft, TextureID::Left);
        ui.arrowLeft.setPosition({85.f, 74.f});
        ui.levelButton.Init(resources, 9);
    }

    void LeaderboardManager::Draw(sf::RenderTexture &texture) const
    {
        texture.draw(ui.background);
        texture.draw(ui.titleFrame);
        texture.draw(ui.title);
        for (int i = 0; i < LEADERBOARD_DISPLAYED; i++)
            if (i + firstDisplayedItem < entries.size())
                texture.draw(ui.entry[i]);

        if (LEADERBOARD_DISPLAYED < entries.size() && firstDisplayedItem + LEADERBOARD_DISPLAYED < entries.size())
            texture.draw(ui.arrowRight);
        if (firstDisplayedItem > 0)
            texture.draw(ui.arrowLeft);

        ui.levelButton.Draw(texture);
    }

    void LeaderboardManager::HandleInput(const sf::Event &event, SoundID &sound)
    {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
        {
            if (entries.size() > 0)
            {
                int previousItem = firstDisplayedItem;
                firstDisplayedItem -= LEADERBOARD_DISPLAYED;
                if (firstDisplayedItem < 0)
                    firstDisplayedItem = ((entries.size() - 1) / LEADERBOARD_DISPLAYED) * LEADERBOARD_DISPLAYED;
                LoadUIEntries();
                if (previousItem != firstDisplayedItem)
                    sound = SoundID::UIMoveHorizontal;
            }
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
        {
            if (entries.size() > 0)
            {
                int previousItem = firstDisplayedItem;
                firstDisplayedItem += LEADERBOARD_DISPLAYED;
                if (firstDisplayedItem > entries.size() - 1)
                    firstDisplayedItem = 0;
                LoadUIEntries();
                if (previousItem != firstDisplayedItem)
                    sound = SoundID::UIMoveHorizontal;
            }
        }
    }

    void LeaderboardManager::LoadUI(const Leaderboard &leaderboard)
    {
        firstDisplayedItem = 0;

        ui.levelButton.SetLevelName(leaderboard.GetLevelName());
        ui.levelButton.SetLevelPreview(leaderboard.GetLevelPreview());
        entries = leaderboard.GetEntries();
        LoadUIEntries();
    }

    void LeaderboardManager::LoadUIEntries()
    {
        for (int i = 0; i < LEADERBOARD_DISPLAYED; i++)
        {
            if (i + firstDisplayedItem < entries.size())
            {
                std::string text = std::to_string(i + firstDisplayedItem + 1) + ".";
                text += entries[i + firstDisplayedItem].playerName;
                std::string score = std::to_string(entries[i + firstDisplayedItem].score);
                int dotNumber = 20 - text.size() - score.size();
                for (int i = 0; i < dotNumber; i++)
                {
                    text += ".";
                }
                ui.entry[i].setString(text + score);
            }
        }
    }
}
