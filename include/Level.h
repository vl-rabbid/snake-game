#pragma once
#include "Constants.h"
#include "GameMath.h"

namespace SnakeGame
{
    enum CellType
    {
        Empty = 0,
        SnakeCell,
        Apple,
        Wall
    };

    struct Cell
    {
        CellType type{};
        sf::RectangleShape shape;
    };

    struct Level
    {
        Cell cells[LEVEL_WIDTH][LEVEL_HEIGHT];
    };

    void InitLevel(Level &level);
    void SpawnApple(Level &level);
    void DrawLevel(Level &level, sf::RenderWindow &window);
    void UpdateCellColor(Level &level, Position2D position);
    void SetCellType(Level &level, Position2D position, CellType cellType);
    CellType GetCellType(Level &level, Position2D position);

}