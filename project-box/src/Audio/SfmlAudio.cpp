#include "./Audio/SfmlAudio.h"
#include "Consts.h"

void SfmlAudio::init()
{
	jumpBuffer_.loadFromFile(JUMP_SOUND_PATH);
	jumpSound_.setBuffer(jumpBuffer_);
	deathBuffer_.loadFromFile(DEATH_SOUND_PATH);
	deathSound_.setBuffer(deathBuffer_);
	bravoBuffer_.loadFromFile(BRAVO_SOUND_PATH);
	bravoSound_.setBuffer(bravoBuffer_);

	music_.setVolume(10);
	music_.setLoop(true);
	music_.openFromFile(MUSIC_PATH);
}

void SfmlAudio::playSound(const SoundType soundType)
{
	switch (soundType) {
	case SoundType::Jump:
		jumpSound_.play();
		break;
	case SoundType::Death:
		deathSound_.play();
		break;
	case SoundType::Bravo:
		bravoSound_.play();
		break;
	case SoundType::None:
		break;
	}
}

void SfmlAudio::stopAllSounds()
{
	jumpSound_.stop();
	deathSound_.stop();
	bravoSound_.stop();
}

void SfmlAudio::stopSound(const SoundType soundType)
{
	switch (soundType) {
	case SoundType::Jump:
		jumpSound_.stop();
		break;
	case SoundType::Death:
		deathSound_.stop();
		break;
	case SoundType::Bravo:
		bravoSound_.stop();
		break;
	case SoundType::None:
		break;
	}
}

void SfmlAudio::playMusic()
{
	music_.play();
}

void SfmlAudio::pauseMusic()
{
	music_.pause();
}

void SfmlAudio::stopMusic()
{
	music_.stop();
}
