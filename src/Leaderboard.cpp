#include "Leaderboard.h"
#include <fstream>
#include <filesystem>

namespace SnakeGame
{
    void Leaderboard::Init(const Resources &resources)
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

    void Leaderboard::Draw(sf::RenderTexture &texture) const
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

    void Leaderboard::HandleInput(const sf::Event &event)
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
                // if (previousItem != firstDisplayedItem)
                // {
                //     PlaySound(game, game.soundFX, game.resources.uiMoveHorizontal);
                // }
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
                // if (previousItem != firstDisplayedItem)
                // {
                //     PlaySound(game, game.soundFX, game.resources.uiMoveHorizontal);
                // }
            }
        }
    }

    bool Leaderboard::LoadFromFile(const LevelConfig &levelConfig)
    {
        levelId = levelConfig.GetId();
        levelName = levelConfig.GetName();
        levelPreview = levelConfig.GenerateLevelPreview();
        firstDisplayedItem = 0;
        entries.clear();
        entries.reserve(LEADERBOARD_SIZE);

        std::ifstream file("leaderboards/" + levelId + ".lb");
        if (file.is_open())
        {
            std::string line;
            while (std::getline(file, line))
            {
                int pos = line.find('=');
                if (pos == std::string::npos)
                    continue;

                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);

                LeaderboardEntry entry;
                entry.playerName = key;
                entry.score = std::stoi(value);
                entries.push_back(entry);
            }
            if (entries.size() > LEADERBOARD_SIZE)
                entries.resize(LEADERBOARD_SIZE);

            file.close();
            return true;
        }
        return false;
    }

    void Leaderboard::AddEntry(const std::string &playerName, int score)
    {
        LeaderboardEntry entry;
        entry.playerName = playerName;
        entry.score = score;
        if (!DoesEntryExists(entry))
        {
            entries.push_back(entry);
            Sort();
            if (entries.size() > LEADERBOARD_SIZE)
                entries.resize(LEADERBOARD_SIZE);
        }
        SaveToFile();
    }

    void Leaderboard::LoadUI()
    {
        ui.levelButton.SetLevelName(levelName);
        ui.levelButton.SetLevelPreview(levelPreview);
        LoadUIEntries();
    }

    void Leaderboard::LoadUIEntries()
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

    bool Leaderboard::DoesEntryExists(const LeaderboardEntry &entry) const
    {
        for (int i = 0; i < entries.size(); i++)
            if (entries[i].playerName == entry.playerName && entries[i].score == entry.score)
                return true;

        return false;
    }

    void Leaderboard::Sort()
    {
        std::sort(
            entries.begin(),
            entries.end(),
            [](const LeaderboardEntry &a, const LeaderboardEntry &b)
            {
                return a.score > b.score;
            });
    }

    bool Leaderboard::SaveToFile()
    {
        const std::filesystem::path directory = "leaderboards";
        std::filesystem::create_directories(directory);
        std::ofstream file("leaderboards/" + levelId + ".lb");
        if (file.is_open())
        {
            for (int i = 0; i < entries.size(); i++)
            {
                file << entries[i].playerName << "=" << entries[i].score << "\n";
            }
            file.close();
            return true;
        }
        return false;
    }
}