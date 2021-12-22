#pragma once
#include "Audio/AudioService.h"
#include "Audio/SoundType.h"

/**
 * \brief An empty implementation of the audio service.
 */
class NullAudio final : public AudioService
{
public:
	void playSound(SoundType soundType) override { /* Do nothing. */ }
	void stopSound(SoundType soundType) override { /* Do nothing. */ }
	void stopAllSounds() override { /* Do nothing. */ }
	void playMusic() override { /* Do nothing. */ }
	void pauseMusic() override { /* Do nothing. */ }
	void stopMusic() override { /* Do nothing. */ }
};
