#pragma once
#include "Game.h"
#include "Renderer.h"

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
        Renderer renderer;
    };
}