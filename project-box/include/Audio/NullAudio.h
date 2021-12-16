#pragma once
#include "Audio/AudioService.h"
#include "Audio/SoundType.h"

class NullAudio final : public AudioService
{
public:
	void playSound(SoundType soundType) override { /* Do nothing. */ }
	void stopSound(SoundType soundType) override { /* Do nothing. */ }
	void stopAllSounds() override { /* Do nothing. */ }
};
