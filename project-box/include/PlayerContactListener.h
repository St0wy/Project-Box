#pragma once

#include "Player.h"

#include <box2d/box2d.h>

class PlayerContactListener final : public b2ContactListener
{
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
	static void CheckStartPlayer(b2Fixture* fixture);
	static void CheckEndPlayer(b2Fixture* fixture);
	static Player* GetPlayerPointer(b2Fixture* fixture);
	static bool IsFootSensor(b2Fixture* fixture);
};