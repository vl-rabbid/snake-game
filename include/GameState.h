#pragma once

namespace SnakeGame
{
    enum class GameState
    {
        MainMenu = 0,
        LevelSelect,
        GameLoop,
        Pause,
        GameOver,
        Leaderboard,
        Exit
    };
}