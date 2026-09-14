#pragma once

namespace SnakeGame
{
    enum class GameState
    {
        Menu = 0,
        GameLoop,
        Delay,
        Exit
    };

    enum class MenuState
    {
        Main = 0,
        Pause,
        GameOver,
        Settings,
        Resolution,
        Difficulty,
        LevelSelect,
        Leaderboard,
        SetPlayerName
    };

    enum class DelayType
    {
        GameStart = 0,
        GameOver
    };

    struct Delay
    {
        float timer;
        float duration;
        GameState nextGameState;
        MenuState nextMenuState;
        DelayType type;
    };

}