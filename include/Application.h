#pragma once
#include "Game.h"

namespace SnakeGame
{
    class Application
    {
    public:
        Application();
        ~Application();

        void Run();

    private:
        Game game;
    };
}