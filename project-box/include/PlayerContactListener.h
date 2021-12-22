#pragma once

#include "Player.h"

#include <box2d/box2d.h>

/**
 * \brief Callback class for the collisions of box2d.
 */
class PlayerContactListener final : public b2ContactListener
{
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;

	/**
	 * \brief Checks if the contact is with a player and sends an action to it.
	 * \param fixture The fixture that is in the contact.
	 */
	static void checkStartPlayer(b2Fixture* fixture);

	/**
	 * \brief Checks if the contact is with a player and sends an action to it.
	 * \param fixture The fixture that is in the contact.
	 */
	static void checkEndPlayer(b2Fixture* fixture);

	/**
	 * \brief Gets the player pointer from the fixture's user data.
	 * \param fixture The fixture that is in the contact.
	 * \return A pointer to the player.
	 */
	static Player* getPlayerPointer(b2Fixture* fixture);

	/**
	 * \brief Checks if the fixture is a foot sensor.
	 * \param fixture The fixture that is in the contact.
	 * \return True if the fixture is a foot sensor.
	 */
	static bool isFootSensor(b2Fixture* fixture);

	/**
	 * \brief Checks if the fixture is a head sensor.
	 * \param fixture The fixture that is in the contact.
	 * \return True if the fixture is a head sensor.
	 */
	static bool isHeadSensor(b2Fixture* fixture);

	/**
	 * \brief Checks if the contact is with a finish line and acts accordingly.
	 * \param fixture The fixture that is in the contact.
	 */
	static void checkStartFinishLine(b2Fixture* fixture);
};