#include "Application.h"

namespace SnakeGame
{
    Application::Application()
    {
        InitGame(game);
    }

    Application::~Application()
    {
        DeinitializeGame(game);
    }

    void Application::Run()
    {
        renderer.SetWindow(RENDER_WIDTH, RENDER_HEIGHT, GAME_NAME);
        renderer.SetWindowScale(GetGameWindowScale(game));

        sf::Clock gameClock;
        float lastTime = gameClock.getElapsedTime().asSeconds();

        while (IsGameRunning(game))
        {
            float currentTime = gameClock.getElapsedTime().asSeconds();
            float deltaTime = currentTime - lastTime;
            lastTime = currentTime;

            sf::Event event;
            while (renderer.WindowPoolEvent(event))
            {
                HandleGameImput(game, event);
            }

            UpdateGame(game, deltaTime);

            renderer.Clear();
            DrawGame(game, renderer.GetTexture());
            renderer.Display();
        }
    }
}