#include "Application.h"

namespace SnakeGame
{
    void Application::Run()
    {
        float windowScale = game.GetWindowScale();
        renderer.SetWindow(RENDER_WIDTH, RENDER_HEIGHT, windowScale, GAME_NAME);

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
                game.HandleInput(event);
            }
            game.Update(deltaTime);
            HandleAppRequest();

            renderer.Clear();
            game.Draw(renderer.GetTexture());
            renderer.Display();
        }
    }

    void Application::HandleAppRequest()
    {
        switch (game.ConsumeAppRequest().type)
        {
        case AppRequestType::None:
            break;
        case AppRequestType::ExitApplication:
            isRunning = false;
            break;
        case AppRequestType::SetWindowScale:
            renderer.SetWindowScale(game.GetWindowScale());
            break;
        default:
            break;
        }
    }
}