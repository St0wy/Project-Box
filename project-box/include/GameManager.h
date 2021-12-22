#pragma once
#include "GameState.h"

/**
 * \brief Class to manage the state of the game.
 */
class GameManager
{
public:
	/**
	 * \brief Gets the state of the game.
	 * \return The state of the game.
	 */
	[[nodiscard]] GameState getState() const;

	/**
	 * \brief Sets the state of the game.
	 * \param state The new state of the game.
	 */
	void setState(GameState state);
private:
	GameState state_ = GameState::Playing;
};
