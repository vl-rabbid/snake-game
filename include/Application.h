#pragma once
#include "Game.h"
#include "Renderer.h"
#include "ApplicationRequest.h"

namespace SnakeGame
{
    class Application
    {
    public:
        Application();
        ~Application();

        void Run();

    private:
        void HandleApplicationRequest();

        Game game;
        Renderer renderer;
        bool isRunning = true;
    };
}