#include "Resources.h"
#include <cassert>
#include <string>
#include <array>

namespace SnakeGame
{
    void InitResources(Resources &resources)
    {
        assert(resources.atlas.loadFromFile(std::string(RESOURCES_PATH) + "/graphics/atlas.png"));
        assert(resources.background.loadFromFile(std::string(RESOURCES_PATH) + "/graphics/background.png"));
        assert(resources.font.loadFromFile(std::string(RESOURCES_PATH) + "/fonts/monogram.ttf"));

        resources.buttonEnabled = CreateNineSliceTexture(resources.atlas, GetTextureRect(TextureID::UIFrame1), 90, 19);
        resources.buttonDisabled = CreateNineSliceTexture(resources.atlas, GetTextureRect(TextureID::UIFrame3), 90, 18);
        resources.buttonPressed = CreateNineSliceTexture(resources.atlas, GetTextureRect(TextureID::UIFrame2), 90, 18);

        resources.subMenu = CreateNineSliceTexture(resources.atlas, GetTextureRect(TextureID::UIFrame3), 120, 113);
        resources.subMenuTitle = CreateNineSliceTexture(resources.atlas, GetTextureRect(TextureID::UIFrame2), 100, 17);

        resources.hud = CreateNineSliceTexture(resources.atlas, GetTextureRect(TextureID::UIFrame4), LEVEL_WIDTH * CELL_SIZE, HUD_HEIGHT * CELL_SIZE);
        resources.hudLevelName = CreateNineSliceTexture(resources.atlas, GetTextureRect(TextureID::UIFrame2), 62, 17);
        resources.hudScore = CreateNineSliceTexture(resources.atlas, GetTextureRect(TextureID::UIFrame2), 95, 17);

        resources.levelSelectButton = CreateNineSliceTexture(resources.atlas, GetTextureRect(TextureID::UIFrame1), 72, 75);
        resources.levelPreviewFrame = CreateNineSliceTexture(resources.atlas, GetTextureRect(TextureID::UIFrame5), 62, 41);

        resources.leaderboardFrame = CreateNineSliceTexture(resources.atlas, GetTextureRect(TextureID::UIFrame3), 133, 84);
        resources.leaderboardLabelFrame = CreateNineSliceTexture(resources.atlas, GetTextureRect(TextureID::UIFrame2), 95, 17);

        resources.inputMenu = CreateNineSliceTexture(resources.atlas, GetTextureRect(TextureID::UIFrame3), 120, 90);
        resources.inputField = CreateNineSliceTexture(resources.atlas, GetTextureRect(TextureID::UIFrame6), 75, 15);

        assert(resources.uiMoveVertical.buffer.loadFromFile(std::string(RESOURCES_PATH) + "/audio/sfx_menu_a.wav"));
        assert(resources.uiMoveHorizontal.buffer.loadFromFile(std::string(RESOURCES_PATH) + "/audio/sfx_menu_b.wav"));
        assert(resources.uiSelect.buffer.loadFromFile(std::string(RESOURCES_PATH) + "/audio/sfx_menu_select.wav"));
        resources.uiSelect.volume = 80.f;
        assert(resources.appleEaten.buffer.loadFromFile(std::string(RESOURCES_PATH) + "/audio/sfx_apple.wav"));
        resources.appleEaten.volume = 80.f;
        assert(resources.wall.buffer.loadFromFile(std::string(RESOURCES_PATH) + "/audio/sfx_wall.wav"));
        resources.wall.volume = 60.f;
        assert(resources.gameOver.buffer.loadFromFile(std::string(RESOURCES_PATH) + "/audio/jingle_game_over.ogg"));
        resources.gameOver.volume = 10.f;
        assert(resources.countdown.buffer.loadFromFile(std::string(RESOURCES_PATH) + "/audio/sfx_countdown.wav"));
        resources.countdown.volume = 70.f;
        assert(resources.countdownGo.buffer.loadFromFile(std::string(RESOURCES_PATH) + "/audio/sfx_countdown_go.wav"));
        resources.countdownGo.volume = 75.f;
        assert(resources.input.buffer.loadFromFile(std::string(RESOURCES_PATH) + "/audio/sfx_input.wav"));
        resources.input.volume = 80.f;

        assert(resources.music.openFromFile(std::string(RESOURCES_PATH) + "/audio/music_theme.ogg"));
        resources.music.setLoop(true);
        resources.music.setVolume(40.f);
    }

    void SetSpriteAtlas(const Resources &resources, sf::Sprite &sprite, TextureID id)
    {
        sprite.setTexture(resources.atlas);
        UpdateSpriteAtlas(sprite, id);
    }

    void UpdateSpriteAtlas(sf::Sprite &sprite, TextureID id)
    {
        sprite.setTextureRect(GetTextureRect(id));
        sprite.setOrigin(GetTextureOrigin(id));
    }

    void SetDefaultText(const Resources &resources, sf::Text &text, const std::string &string)
    {
        text.setString(string);
        text.setFont(resources.font);
        text.setCharacterSize(16);
        text.setFillColor(COLOR_TEXT);
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

        case TextureID::Wall1:
            return sf::IntRect(0, 36, 12, 12);
            break;
        case TextureID::Wall2:
            return sf::IntRect(12, 36, 12, 12);
            break;
        case TextureID::Wall3:
            return sf::IntRect(24, 36, 12, 12);
            break;
        case TextureID::Wall4:
            return sf::IntRect(36, 36, 12, 12);
            break;
        case TextureID::Wall5:
            return sf::IntRect(48, 36, 12, 12);
            break;
        case TextureID::Wall6:
            return sf::IntRect(60, 36, 12, 12);
            break;
        case TextureID::Wall7:
            return sf::IntRect(72, 36, 12, 12);
            break;
        case TextureID::Wall8:
            return sf::IntRect(84, 36, 12, 12);
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

        case TextureID::SliderVertical:
            return sf::IntRect(84, 48, 12, 12);
            break;

        case TextureID::Up:
            return sf::IntRect(96, 48, 12, 12);
            break;
        case TextureID::Down:
            return sf::IntRect(108, 48, 12, 12);
            break;

        case TextureID::UIFrame4:
            return sf::IntRect(120, 48, 12, 12);
            break;
        case TextureID::UIFrame5:
            return sf::IntRect(132, 48, 12, 12);
            break;

        case TextureID::Left:
            return sf::IntRect(0, 60, 12, 12);
            break;
        case TextureID::Right:
            return sf::IntRect(12, 60, 12, 12);
            break;

        case TextureID::SliderHorizontal:
            return sf::IntRect(24, 60, 12, 12);
            break;

        case TextureID::UIFrame6:
            return sf::IntRect(36, 60, 12, 12);
            break;

        default:
            break;
        }
        return sf::IntRect(0, 0, 12, 12);
    }

    sf::Vector2f GetTextureOrigin(TextureID id)
    {
        switch (id)
        {
        case TextureID::SelectorTopLeft:
            return {2.f, 3.f};
            break;
        case TextureID::SelectorTopRight:
            return {6.f, 3.f};
            break;
        case TextureID::SelectorBottomLeft:
            return {2.f, 11.f};
            break;
        case TextureID::SelectorBottomRight:
            return {6.f, 11.f};
            break;

        case TextureID::Right:
            return {6.f, 4.f};
            break;
        case TextureID::Left:
            return {0.f, 4.f};
            break;
        case TextureID::Up:
            return {4.f, 8.f};
            break;
        case TextureID::Down:
            return {4.f, 0.f};
            break;
        case TextureID::SliderHorizontal:
            return {5.f, 3.f};
            break;
        case TextureID::SliderVertical:
            return {3.f, 5.f};
            break;

        default:
            return {0.f, 0.f};
            break;
        }
    }

    sf::IntRect GetRandomWallRect()
    {
        static std::array<TextureID, 8> walls =
            {
                TextureID::Wall1,
                TextureID::Wall2,
                TextureID::Wall3,
                TextureID::Wall4,
                TextureID::Wall5,
                TextureID::Wall6,
                TextureID::Wall7,
                TextureID::Wall8};
        int textureId = GetRandomInt(0, walls.size() - 1);
        return GetTextureRect(walls[textureId]);
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