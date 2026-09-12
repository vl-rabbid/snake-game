#pragma once
#include "Constants.h"
#include "GameMath.h"
#include "Resources.h"
#include "LevelConfig.h"

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

    struct Level
    {
        LevelConfig config;
        std::vector<Wall> walls;
        Apple apple;
        int countEmptyCells;
    };

    void InitLevel(Level &level, Resources &resources);
    void SpawnApple(Level &level);
    void DrawLevel(Level &level, sf::RenderTexture &texture);
}