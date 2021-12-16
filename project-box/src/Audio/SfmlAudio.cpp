#include "./Audio/SfmlAudio.h"
#include "Consts.h"

sf::SoundBuffer SfmlAudio::jumpBuffer_;
sf::Sound SfmlAudio::jumpSound_;

void SfmlAudio::init()
{
	jumpBuffer_.loadFromFile(JUMP_SOUND_PATH);
	jumpSound_.setBuffer(jumpBuffer_);
}

void SfmlAudio::playSound(const SoundType soundType)
{
	switch (soundType) {
	case SoundType::Jump:
		jumpSound_.play();
		break;
	case SoundType::None:
		break;
	}
}

void SfmlAudio::stopAllSounds()
{
	jumpSound_.stop();
}

void SfmlAudio::stopSound(const SoundType soundType)
{
	switch (soundType) {
	case SoundType::Jump:
		jumpSound_.stop();
		break;
	case SoundType::None:
		break;
	}
}
