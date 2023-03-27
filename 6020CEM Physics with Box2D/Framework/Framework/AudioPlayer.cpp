#include "AudioPlayer.h"
#include <iostream>

AudioPlayer::AudioPlayer(std::string _soundPath) : Component(Component::typeOfComponent::Audio, uniqueComponentIdIdentifier)
{
    soundPath = _soundPath;
    if (!soundSource.loadFromFile(soundPath))
    {
        std::cout << "Error: fail trying to load audio" << std::endl;
        return;
    }

    sound.setBuffer(soundSource);
}

AudioPlayer::~AudioPlayer()
{
}

void AudioPlayer::PlaySound()
{
    sound.play();
}

void AudioPlayer::Start()
{
}
