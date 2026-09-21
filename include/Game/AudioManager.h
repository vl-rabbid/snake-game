#pragma once
#include <SFML/Audio.hpp>
#include "Game/Resources.h"

namespace SnakeGame
{
    struct GameSound
    {
        sf::SoundBuffer buffer;
        float volume = 100.f;
        int trackNumber = 0;
    };

    enum class SoundID
    {
        None = 0,
        UIMoveVertical,
        UIMoveHorizontal,
        UISelect,
        AppleEaten,
        Wall,
        GameOver,
        Countdown,
        CountdownGo,
        Input,
    };

    class AudioManager
    {
    public:
        void Init();
        void PlaySound(const SoundID &id, bool soundEnabled);
        void PlayMusic(bool musicEnabled);
        void StopMusic();
        void PauseMusic();

    private:
        GameSound &GetGameSound(const SoundID &id);

        sf::Sound audioTracks[AUDIO_TRACK_COUNT];
        sf::Music music;

        GameSound uiMoveVertical;
        GameSound uiMoveHorizontal;
        GameSound uiSelect;
        GameSound appleEaten;
        GameSound wall;
        GameSound gameOver;
        GameSound countdown;
        GameSound countdownGo;
        GameSound input;
    };

}
