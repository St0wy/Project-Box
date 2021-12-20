#include "./Audio/SfmlAudio.h"
#include "Consts.h"

void SfmlAudio::init()
{
	jumpBuffer_.loadFromFile(JUMP_SOUND_PATH);
	jumpSound_.setBuffer(jumpBuffer_);
	deathBuffer_.loadFromFile(DEATH_SOUND_PATH);
	deathSound_.setBuffer(deathBuffer_);
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
	case SoundType::None:
		break;
	}
}

void SfmlAudio::stopAllSounds()
{
	jumpSound_.stop();
	deathSound_.stop();
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
	case SoundType::None:
		break;
	}
}
