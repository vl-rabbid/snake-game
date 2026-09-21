#pragma once

namespace SnakeGame
{
    enum class AppRequestType
    {
        None = 0,
        ExitApplication,
        SetWindowScale
    };

    struct AppRequest
    {
        AppRequestType type = AppRequestType::None;
    };

}
