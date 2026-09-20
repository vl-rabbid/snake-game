#include "AudioManager.h"
#include <cassert>

namespace SnakeGame
{
    void AudioManager::Init()
    {
        assert(uiMoveVertical.buffer.loadFromFile(std::string(RESOURCES_PATH) + "/audio/sfx_menu_a.wav"));
        assert(uiMoveHorizontal.buffer.loadFromFile(std::string(RESOURCES_PATH) + "/audio/sfx_menu_b.wav"));
        assert(uiSelect.buffer.loadFromFile(std::string(RESOURCES_PATH) + "/audio/sfx_menu_select.wav"));
        uiSelect.volume = 80.f;
        assert(appleEaten.buffer.loadFromFile(std::string(RESOURCES_PATH) + "/audio/sfx_apple.wav"));
        appleEaten.volume = 80.f;
        assert(wall.buffer.loadFromFile(std::string(RESOURCES_PATH) + "/audio/sfx_wall.wav"));
        wall.volume = 60.f;
        assert(gameOver.buffer.loadFromFile(std::string(RESOURCES_PATH) + "/audio/jingle_game_over.ogg"));
        gameOver.volume = 10.f;
        gameOver.trackNumber = 1;
        assert(countdown.buffer.loadFromFile(std::string(RESOURCES_PATH) + "/audio/sfx_countdown.wav"));
        countdown.volume = 70.f;
        assert(countdownGo.buffer.loadFromFile(std::string(RESOURCES_PATH) + "/audio/sfx_countdown_go.wav"));
        countdownGo.volume = 75.f;
        assert(input.buffer.loadFromFile(std::string(RESOURCES_PATH) + "/audio/sfx_input.wav"));
        input.volume = 80.f;

        assert(music.openFromFile(std::string(RESOURCES_PATH) + "/audio/music_theme.ogg"));
        music.setLoop(true);
        music.setVolume(40.f);
    }

    void AudioManager::PlaySound(const SoundID &id, bool soundEnabled)
    {
        if (soundEnabled && id != SoundID::None)
        {
            GameSound &sound = GetGameSound(id);
            if (sound.trackNumber < AUDIO_TRACK_COUNT)
            {
                audioTracks[sound.trackNumber].setVolume(sound.volume);
                audioTracks[sound.trackNumber].setBuffer(sound.buffer);
                audioTracks[sound.trackNumber].play();
            }
        }
    }

    void AudioManager::PlayMusic(bool musicEnabled)
    {
        if (musicEnabled)
            music.play();
    }

    void AudioManager::StopMusic()
    {
        music.stop();
    }

    void AudioManager::PauseMusic()
    {
        music.pause();
    }

    GameSound &AudioManager::GetGameSound(const SoundID &id)
    {
        switch (id)
        {
        case SoundID::UIMoveVertical:
            return uiMoveVertical;
            break;
        case SoundID::UIMoveHorizontal:
            return uiMoveHorizontal;
            break;
        case SoundID::UISelect:
            return uiSelect;
            break;
        case SoundID::AppleEaten:
            return appleEaten;
            break;
        case SoundID::Wall:
            return wall;
            break;
        case SoundID::GameOver:
            return gameOver;
            break;
        case SoundID::Countdown:
            return countdown;
            break;
        case SoundID::CountdownGo:
            return countdownGo;
            break;
        case SoundID::Input:
            return input;
            break;
        default:
            break;
        }
        return uiMoveVertical;
    }
}
