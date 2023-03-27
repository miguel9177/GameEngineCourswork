#pragma once
#include "Component.h"
#include <SFML/Audio.hpp>

class AudioPlayer : public Component
{
private:
	sf::SoundBuffer soundSource;
	sf::Sound sound;
	std::string soundPath;
public:
	static const unsigned int uniqueComponentIdIdentifier = 200;

	AudioPlayer(std::string soundPath);
	~AudioPlayer();

	void PlaySound();
	void Start() override;

	inline std::string GetAudioPath() { return soundPath; };
};

