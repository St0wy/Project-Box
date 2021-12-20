#pragma once
#include "AudioService.h"
#include <SFML/Audio.hpp>

class SfmlAudio final : public AudioService
{
public:
	void init();
	void playSound(SoundType soundType) override;
	void stopAllSounds() override;
	void stopSound(SoundType soundType) override;
private:
	sf::SoundBuffer jumpBuffer_;
	sf::Sound jumpSound_;
	sf::SoundBuffer deathBuffer_;
	sf::Sound deathSound_;
};