#pragma once
#include "Game/Constants.h"
#include "Game/GameMath.h"
#include "Game/Resources.h"
#include "Game/LevelConfig.h"

namespace SnakeGame
{
    struct Apple
    {
        Position2D position;
        sf::Sprite sprite;
    };

    struct Wall
    {
        Position2D position;
        sf::Sprite sprite;
    };

    class Level
    {
    public:
        void Init(const LevelConfig &config, const Resources &resources);
        void ResetState();
        void SpawnApple();
        void Draw(sf::RenderTexture &texture) const;

        void SetState(const Position2D &position, const CellType &type);
        CellType GetState(const Position2D &position) const;

        Position2D GetApplePosition() const;
        const std::string &GetId() const;
        const std::string &GetName() const;
        Position2D GetSnakeSpawn() const;
        int GetSnakeSize() const;
        int GetMaxSnakeLength() const;

    private:
        std::string id;
        std::string name;
        Position2D snakeSpawn;
        int snakeSize;

        CellGrid state;
        std::vector<Wall> walls;
        Apple apple;
        int maxSnakeLength;
    };
}