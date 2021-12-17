#pragma once

#include "Player.h"

#include <box2d/box2d.h>

class PlayerContactListener final : public b2ContactListener
{
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
	static void checkStartPlayer(b2Fixture* fixture);
	static void checkEndPlayer(b2Fixture* fixture);
	static Player* getPlayerPointer(b2Fixture* fixture);
	static bool isFootSensor(b2Fixture* fixture);
	static void checkStartFlag(b2Fixture* fixture);
};