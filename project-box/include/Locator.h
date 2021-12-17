#pragma once
#include "GameManager.h"

#include "Audio/AudioService.h"
#include "Audio/NullAudio.h"
#include "Texture/TextureService.h"

class Locator
{
public:
	static void init();
	static AudioService* getAudio();
	static TextureService* getTextureService();
	static GameManager* getGameManager();
	static void provide(AudioService* service);
	static void provide(TextureService* service);
	static void provide(GameManager* gameManager);
private:
	static AudioService* audioService_;
	static NullAudio nullService_;
	static TextureService* textureService_;
	static GameManager* gameManager_;
};