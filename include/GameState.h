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
        Delay,
        Exit
    };

    enum class DelayType
    {
        Countdown = 0,
        GameOver
    };

    struct Delay
    {
        float timer;
        float duration;
        GameState nextState;
        DelayType type;
    };

}