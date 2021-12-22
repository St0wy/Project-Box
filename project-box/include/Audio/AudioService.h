#pragma once
#include "SoundType.h"

/**
 * \brief Base virtual class for all audio services.
 */
class AudioService {
public:
	virtual ~AudioService() = default;
	/**
	 * \brief Plays the requested sound.
	 * \param soundType The "id" of the sound to play.
	 */
	virtual void playSound(SoundType soundType) = 0;

	/**
	 * \brief Stops the requested sound.
	 * \param soundType The "id" of the sound to play.
	 */
	virtual void stopSound(SoundType soundType) = 0;

	/**
	 * \brief Stops all the sounds.
	 */
	virtual void stopAllSounds() = 0;

	/**
	 * \brief Plays the music of the game.
	 */
	virtual void playMusic() = 0;

	/**
	 * \brief Pauses the music.
	 */
	virtual void pauseMusic() = 0;

	/**
	 * \brief Stops the music.
	 */
	virtual void stopMusic() = 0;
};