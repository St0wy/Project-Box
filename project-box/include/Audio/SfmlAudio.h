#pragma once
#include "AudioService.h"
#include <SFML/Audio.hpp>

class SfmlAudio final : public AudioService
{
public:
	static void init();
	void playSound(SoundType soundType) override;
	void stopAllSounds() override;
	void stopSound(SoundType soundType) override;
private:
	static sf::SoundBuffer jumpBuffer_;
	static sf::Sound jumpSound_;
};