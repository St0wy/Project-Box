#pragma once
#include "AudioService.h"
#include <SFML/Audio.hpp>

/**
 * \brief An SFML implementation of the audio service.
 */
class SfmlAudio final : public AudioService
{
public:
	/**
	 * \brief Loads all the sounds into memory.
	 */
	void init();
	void playSound(SoundType soundType) override;
	void stopAllSounds() override;
	void stopSound(SoundType soundType) override;
	void playMusic() override;
	void pauseMusic() override;
	void stopMusic() override;
private:
	sf::SoundBuffer jumpBuffer_;
	sf::Sound jumpSound_;
	sf::SoundBuffer deathBuffer_;
	sf::Sound deathSound_;
	sf::SoundBuffer bravoBuffer_;
	sf::Sound bravoSound_;
	sf::Music music_;
};