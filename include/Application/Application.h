#pragma once
#include "Game/Game.h"
#include "Application/Renderer.h"
#include "Application/AppRequest.h"

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