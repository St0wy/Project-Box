#include "PlayerContactListener.h"

#include "FinishLine.h"
#include "Player.h"
#include "FixtureType.h"
#include "GameManager.h"
#include "Locator.h"

void PlayerContactListener::BeginContact(b2Contact* contact)
{
	b2ContactListener::BeginContact(contact);
	const auto fixtureA = contact->GetFixtureA();
	const auto fixtureB = contact->GetFixtureB();
	checkStartPlayer(fixtureA);
	checkStartPlayer(fixtureB);
	checkStartFlag(fixtureA);
	checkStartFlag(fixtureB);
}

void PlayerContactListener::EndContact(b2Contact* contact)
{
	b2ContactListener::EndContact(contact);
	checkEndPlayer(contact->GetFixtureA());
	checkEndPlayer(contact->GetFixtureB());
}

void PlayerContactListener::checkStartPlayer(b2Fixture* fixture)
{
	if (Player* player = getPlayerPointer(fixture); player && isFootSensor(fixture))
	{
		player->StartContact();
	}
}

void PlayerContactListener::checkEndPlayer(b2Fixture* fixture)
{
	if (Player* player = getPlayerPointer(fixture); player && isFootSensor(fixture))
	{
		player->EndContact();
	}
}

Player* PlayerContactListener::getPlayerPointer(b2Fixture* fixture)
{
	const std::uintptr_t bodyUserData = fixture->GetBody()->GetUserData().pointer;
	const auto ptr = reinterpret_cast<Entity*>(bodyUserData);  // NOLINT(performance-no-int-to-ptr)
	const auto playerPtr = dynamic_cast<Player*>(ptr);
	return playerPtr;
}

bool PlayerContactListener::isFootSensor(b2Fixture* fixture)
{
	const auto pointer = fixture->GetUserData().pointer;
	constexpr auto sensorPtr = static_cast<uintptr_t>(FixtureType::PlayerFootSensor);
	return pointer == sensorPtr;
}

void PlayerContactListener::checkStartFlag(b2Fixture* fixture)
{
	const std::uintptr_t bodyUserData = fixture->GetBody()->GetUserData().pointer;
	// ReSharper disable once CppTooWideScopeInitStatement
	const auto ptr = reinterpret_cast<Entity*>(bodyUserData);  // NOLINT(performance-no-int-to-ptr)
	if (dynamic_cast<FinishLine*>(ptr))
	{
		GameManager* gm = Locator::getGameManager();
		gm->setState(GameState::Winning);
	}
}
