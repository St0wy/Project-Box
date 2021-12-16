#include "Locator.h"

AudioService* Locator::audioService_ = nullptr;
NullAudio Locator::nullService_;

void Locator::init()
{
	audioService_ = &nullService_;
}

AudioService* Locator::getAudio()
{
	return audioService_;
}

void Locator::provide(AudioService* service)
{
	if (!service)
	{
		// Revert to null service
		audioService_ = &nullService_;
	}
	else
	{
		audioService_ = service;
	}
}
