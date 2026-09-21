#pragma once
#include "Game/GameMath.h"

namespace SnakeGame
{
    enum class CellType
    {
        Empty = 0,
        Snake,
        Apple,
        Wall
    };

    class CellGrid
    {
    public:
        void SetCellType(const Position2D &position, const CellType &type);
        CellType GetCellType(const Position2D &position) const;
        void SetEmpty();

    private:
        CellType cells[LEVEL_WIDTH][LEVEL_HEIGHT];
    };

    class LevelConfig
    {
    public:
        void LoadFromFile(const std::string &filePath);
        void UpdatePreviewCells();
        void SetEmpty();
        sf::VertexArray GenerateLevelPreview() const;

        const std::string &GetId() const;
        const std::string &GetName() const;
        const std::vector<Position2D> &GetWalls() const;
        const Position2D &GetSnakeSpawn() const;
        int GetSnakeSize() const;

    private:
        std::string id;
        std::string name;
        std::vector<Position2D> walls;
        Position2D snakeSpawn;
        int snakeSize;
        CellGrid previewCells;
    };
}
