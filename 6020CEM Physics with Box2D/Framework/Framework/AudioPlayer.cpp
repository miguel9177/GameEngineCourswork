#include "AudioPlayer.h"
#include <iostream>
#include "EngineFunctionalityManager.h"

AudioPlayer::AudioPlayer(std::string _soundPath) : Component(Component::typeOfComponent::Audio, uniqueComponentIdIdentifier)
{
    //stores the sound path
    soundPath = _soundPath;
    //create a new sound source
    soundSource = new sf::SoundBuffer();
    if (!soundSource->loadFromFile(soundPath))
    {
        std::cout << "Error: fail trying to load audio" << std::endl;
        return;
    }

    //create a new sound object
    sound = new sf::Sound();
    //set its buffer
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
    //if on play mode play the sound
    if(EngineFunctionalityManager::GetInstance()->GetEngineState() == EngineFunctionalityManager::State::playMode && sound != nullptr && soundSource != nullptr)
        sound->play();
}

void AudioPlayer::Start()
{
}
