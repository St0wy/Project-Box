#include "Locator.h"

AudioService* Locator::audioService_ = nullptr;
TextureService* Locator::textureService_ = nullptr;
GameManager* Locator::gameManager_ = nullptr;
NullAudio Locator::nullService_;

void Locator::init()
{
	audioService_ = &nullService_;
}

AudioService* Locator::getAudio()
{
	return audioService_;
}

TextureService* Locator::getTextureService()
{
	return textureService_;
}

GameManager* Locator::getGameManager()
{
	return gameManager_;
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

void Locator::provide(TextureService* service)
{
	textureService_ = service;
}

void Locator::provide(GameManager* gameManager)
{
	gameManager_ = gameManager;
}
