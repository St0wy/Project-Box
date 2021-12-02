#include "PlayerContactListener.h"
#include "Player.h"
#include "SensorType.h"

void PlayerContactListener::BeginContact(b2Contact* contact)
{
	b2ContactListener::BeginContact(contact);
	CheckStartPlayer(contact->GetFixtureA());
	CheckStartPlayer(contact->GetFixtureB());
}

void PlayerContactListener::EndContact(b2Contact* contact)
{
	b2ContactListener::EndContact(contact);
	CheckEndPlayer(contact->GetFixtureA());
	CheckEndPlayer(contact->GetFixtureB());
}

void PlayerContactListener::CheckStartPlayer(b2Fixture* fixture)
{
	if (Player* player = GetPlayerPointer(fixture); player && IsFootSensor(fixture))
	{
		player->StartContact();
	}
}

void PlayerContactListener::CheckEndPlayer(b2Fixture* fixture)
{
	if (Player* player = GetPlayerPointer(fixture); player && IsFootSensor(fixture))
	{
		player->EndContact();
	}
}

Player* PlayerContactListener::GetPlayerPointer(b2Fixture* fixture)
{
	const std::uintptr_t bodyUserData = fixture->GetBody()->GetUserData().pointer;
	return reinterpret_cast<Player*>(bodyUserData);
}

bool PlayerContactListener::IsFootSensor(b2Fixture* fixture)
{
	return fixture->GetUserData().pointer == static_cast<uintptr_t>(SensorType::PlayerFootSensor);
}
