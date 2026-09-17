#include "LevelConfig.h"
#include <fstream>
#include <filesystem>

namespace SnakeGame
{
    void CellGrid::SetCellType(const Position2D &position, const CellType &type)
    {
        cells[position.x][position.y] = type;
    }

    CellType CellGrid::GetCellType(const Position2D &position) const
    {
        return cells[position.x][position.y];
    }

    void CellGrid::SetEmpty()
    {
        for (int x = 0; x < LEVEL_WIDTH; x++)
        {
            for (int y = 0; y < LEVEL_HEIGHT; y++)
            {
                SetCellType({x, y}, CellType::Empty);
            }
        }
    }

    void LevelConfig::LoadFromFile(const std::string &filePath)
    {
        SetEmpty();
        std::filesystem::path path = filePath;
        id = path.stem().string();
        std::ifstream file(filePath);
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

                if (key == "name")
                    name = value;
                else if (key == "snakeSpawn")
                    snakeSpawn = ParsePosition(value);
                else if (key == "snakeSize")
                    snakeSize = std::stoi(value);
                else if (key == "wallCount")
                    walls.reserve(std::stoi(value));
                else if (key == "wall")
                    walls.push_back(ParsePosition(value));
            }
            file.close();
        }
        UpdatePreviewCells();
    }

    void LevelConfig::UpdatePreviewCells()
    {
        for (auto &wall : walls)
            previewCells.SetCellType(wall, CellType::Wall);

        Position2D snakePosition = snakeSpawn;
        for (int i = 0; i < snakeSize; i++)
        {
            previewCells.SetCellType(snakePosition, CellType::Snake);
            snakePosition.y += 1;
        }
    }

    void LevelConfig::SetEmpty()
    {
        id = "empty";
        name = "Empty";
        snakeSpawn = {LEVEL_WIDTH / 2, (LEVEL_HEIGHT / 2)};
        snakeSize = 3;
        walls.clear();

        previewCells.SetEmpty();
    }

    sf::VertexArray LevelConfig::GenerateLevelPreview() const
    {
        sf::VertexArray vertices(
            sf::Quads,
            LEVEL_WIDTH * LEVEL_HEIGHT * 4);

        for (int y = 0; y < LEVEL_HEIGHT; y++)
        {
            for (int x = 0; x < LEVEL_WIDTH; x++)
            {
                sf::Color color;
                if (previewCells.GetCellType({x, y}) == CellType::Empty)
                {
                    if ((x + y) % 2 == 0)
                        color = COLOR_GREEN_LIGHT;
                    else
                        color = COLOR_GREEN_DARK;
                }
                else if (previewCells.GetCellType({x, y}) == CellType::Wall)
                    color = COLOR_WALL;

                else if (previewCells.GetCellType({x, y}) == CellType::Snake)
                    color = COLOR_SNAKE;

                int index = (y * LEVEL_WIDTH + x) * 4;

                vertices[index + 0] = sf::Vertex(sf::Vector2f(x, y), color);
                vertices[index + 1] = sf::Vertex(sf::Vector2f(x + 1, y), color);
                vertices[index + 2] = sf::Vertex(sf::Vector2f(x + 1, y + 1), color);
                vertices[index + 3] = sf::Vertex(sf::Vector2f(x, y + 1), color);
            }
        }
        return vertices;
    }

    const std::string &LevelConfig::GetId() const
    {
        return id;
    }

    const std::string &LevelConfig::GetName() const
    {
        return name;
    }

    const std::vector<Position2D> &LevelConfig::GetWalls() const
    {
        return walls;
    }

    const Position2D &LevelConfig::GetSnakeSpawn() const
    {
        return snakeSpawn;
    }

    int LevelConfig::GetSnakeSize() const
    {
        return snakeSize;
    }
}