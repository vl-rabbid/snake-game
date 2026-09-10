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

    struct Wall
    {
        Position2D position;
        sf::Sprite sprite;
    };

    struct Level
    {
        std::string name;
        Cell cells[LEVEL_WIDTH][LEVEL_HEIGHT];
        std::vector<Wall> walls;
        Apple apple;
        sf::Sprite background;

        int countEmptyCells;
    };

    void InitLevel(Level &level, Resources &resources);
    void SpawnApple(Level &level);
    void DrawLevel(Level &level, sf::RenderTexture &texture);
    void SetCellType(Level &level, Position2D position, CellType cellType);
    CellType GetCellType(Level &level, Position2D position);

}