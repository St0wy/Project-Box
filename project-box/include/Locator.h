#pragma once
#include "Audio/AudioService.h"
#include "Audio/NullAudio.h"

class Locator
{
public:
	static void init();
	static AudioService* getAudio();
	static void provide(AudioService* service);
private:
	static AudioService* audioService_;
	static NullAudio nullService_;
};