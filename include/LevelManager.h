#pragma once
#include "GameMath.h"
#include "LevelConfig.h"
#include "UIComponents.h"
#include "MenuCommand.h"

namespace SnakeGame
{
    struct LevelManagerUI
    {
        std::vector<LevelButton> buttons;
        Selector selector;
        sf::RectangleShape sliderBar;
        sf::Sprite slider;
        float sliderTargetPositionX;
        sf::Sprite arrowRight;
        sf::Sprite arrowLeft;
    };

    class LevelManager
    {
    public:
        void Init(const Resources &resources);
        void Update(const float deltaTime);
        void Draw(sf::RenderTexture &texture) const;
        void HandleInput(MenuCommand &command, const sf::Event &event);
        void LoadFromFiles();

        const LevelConfig &GetSelectedLevelConfig() const;

    private:
        void LoadUI();
        void LoadUIButtons();
        void SetSelector();

        std::vector<LevelConfig> levels;
        int selected;
        int firstDisplayedItem;
        LevelManagerUI ui;
    };
}
