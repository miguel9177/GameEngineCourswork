#include "AudioPlayer.h"
#include <iostream>
#include "EngineFunctionalityManager.h"

AudioPlayer::AudioPlayer(std::string _soundPath) : Component(Component::typeOfComponent::Audio, uniqueComponentIdIdentifier)
{
    soundPath = _soundPath;
    soundSource = new sf::SoundBuffer();
    if (!soundSource->loadFromFile(soundPath))
    {
        std::cout << "Error: fail trying to load audio" << std::endl;
        return;
    }

    sound = new sf::Sound();
    sound->setBuffer(*soundSource);
}

AudioPlayer::~AudioPlayer()
{
    delete sound;
    sound = nullptr;
    delete soundSource;
    soundSource = nullptr;
}

void AudioPlayer::PlaySound()
{
    if(EngineFunctionalityManager::GetInstance()->GetEngineState() == EngineFunctionalityManager::State::playMode && sound != nullptr && soundSource != nullptr)
        sound->play();
}

void AudioPlayer::Start()
{
}
