#pragma once
#include "Constants.h"
#include "GameMath.h"
#include "Resources.h"

namespace SnakeGame
{
    enum class CellType
    {
        Empty = 0,
        Snake,
        Apple,
        Wall
    };

    struct Cell
    {
        CellType type{};
    };

    struct Apple
    {
        Position2D position;
        sf::Sprite sprite;
    };

    struct Level
    {
        Cell cells[LEVEL_WIDTH][LEVEL_HEIGHT];
        Apple apple;
        sf::Sprite background;
    };

    void InitLevel(Level &level, Resources &resources);
    void SpawnApple(Level &level);
    void DrawLevel(Level &level, sf::RenderTexture &texture);
    void SetCellType(Level &level, Position2D position, CellType cellType);
    CellType GetCellType(Level &level, Position2D position);

}