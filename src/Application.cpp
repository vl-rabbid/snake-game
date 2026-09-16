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

        while (isRunning)
        {
            float currentTime = gameClock.getElapsedTime().asSeconds();
            float deltaTime = currentTime - lastTime;
            lastTime = currentTime;

            sf::Event event;
            while (renderer.WindowPollEvent(event))
            {
                HandleGameImput(game, event);
            }
            UpdateGame(game, deltaTime);
            HandleApplicationRequest();

            renderer.Clear();
            DrawGame(game, renderer.GetTexture());
            renderer.Display();
        }
    }

    void Application::HandleApplicationRequest()
    {
        switch (GetApplicationRequest(game).type)
        {
        case ApplicationRequestType::None:
            break;
        case ApplicationRequestType::ExitApplication:
            isRunning = false;
            break;
        case ApplicationRequestType::SetWindowScale:
            renderer.SetWindowScale(GetGameWindowScale(game));
            break;
        default:
            break;
        }
    }
}