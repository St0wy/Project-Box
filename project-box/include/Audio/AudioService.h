#pragma once
#include "SoundType.h"

class AudioService {
public:
	virtual ~AudioService() = default;
	virtual void playSound(SoundType soundType) = 0;
	virtual void stopSound(SoundType soundType) = 0;
	virtual void stopAllSounds() = 0;
};