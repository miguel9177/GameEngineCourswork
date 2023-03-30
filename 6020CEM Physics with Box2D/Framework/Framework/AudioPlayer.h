#pragma once
#include "Component.h"
#include <SFML/Audio.hpp>

//this adds a player sound
class AudioPlayer : public Component
{
private:
	//this stores the sound source
	sf::SoundBuffer* soundSource;
	//stores the sound object
	sf::Sound* sound;
	//stores the path to the soudn
	std::string soundPath;
public:
	//this is a unique id identifier, read documentation graph to fully understand its reason, but in short everty component needs an unique identifier
	static const unsigned int uniqueComponentIdIdentifier = 301;

	AudioPlayer(std::string soundPath);
	~AudioPlayer();

	//playes the given sound
	void PlaySound();
	void Start() override;

	//returns the audio path
	inline std::string GetAudioPath() { return soundPath; };
};

