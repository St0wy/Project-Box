#pragma once
#include "GameManager.h"

#include "Audio/AudioService.h"
#include "Audio/NullAudio.h"
#include "Texture/TextureService.h"

/**
 * \brief The class used to locate different services.
 */
class Locator
{
public:
	/**
	 * \brief Initialises the services.
	 */
	static void init();

	/**
	 * \brief Gets the audio service.
	 * \return A pointer to the audio service.
	 */
	static AudioService* getAudio();

	/**
	 * \brief Gets the texture service.
	 * \return A pointer to the texture service.
	 */
	static TextureService* getTextureService();

	/**
	 * \brief Gets the game manager.
	 * \return A pointer to the game manager.
	 */
	static GameManager* getGameManager();

	/**
	 * \brief Provides the audio service.
	 * \param service The new audio service to use.
	 */
	static void provide(AudioService* service);

	/**
	 * \brief Provides the texture service.
	 * \param service The new texture service.
	 */
	static void provide(TextureService* service);

	/**
	 * \brief Provides the game manager.
	 * \param gameManager The new game manager.
	 */
	static void provide(GameManager* gameManager);
private:
	static AudioService* audioService_;
	static NullAudio nullService_;
	static TextureService* textureService_;
	static GameManager* gameManager_;
};