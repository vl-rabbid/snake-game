#pragma once
#include "Game.h"
#include "Renderer.h"
#include "AppRequest.h"

namespace SnakeGame
{
    class Application
    {
    public:
        void Run();

    private:
        void HandleAppRequest();

        Game game;
        Renderer renderer;
        bool isRunning = true;
    };
}