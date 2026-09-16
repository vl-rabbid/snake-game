#pragma once

namespace SnakeGame
{
    enum class ApplicationRequestType
    {
        None = 0,
        ExitApplication,
        SetWindowScale
    };

    struct ApplicationRequest
    {
        ApplicationRequestType type = ApplicationRequestType::None;
    };

}
