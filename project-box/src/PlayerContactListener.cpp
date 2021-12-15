#include "PlayerContactListener.h"

#include "FinishLine.h"
#include "Player.h"
#include "FixtureType.h"
#include "GameManager.h"

void PlayerContactListener::BeginContact(b2Contact* contact)
{
	b2ContactListener::BeginContact(contact);
	const auto fixtureA = contact->GetFixtureA();
	const auto fixtureB = contact->GetFixtureB();
	CheckStartPlayer(fixtureA);
	CheckStartPlayer(fixtureB);
	CheckStartFlag(fixtureA);
	CheckStartFlag(fixtureB);
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
	const auto ptr = reinterpret_cast<Entity*>(bodyUserData);
	const auto playerPtr = dynamic_cast<Player*>(ptr);
	return playerPtr;
}

bool PlayerContactListener::IsFootSensor(b2Fixture* fixture)
{
	const auto pointer = fixture->GetUserData().pointer;
	constexpr auto sensorPtr = static_cast<uintptr_t>(FixtureType::PlayerFootSensor);
	return pointer == sensorPtr;
}

void PlayerContactListener::CheckStartFlag(b2Fixture* fixture)
{
	const std::uintptr_t bodyUserData = fixture->GetBody()->GetUserData().pointer;
	const auto ptr = reinterpret_cast<Entity*>(bodyUserData);
	if (const auto finishLinePtr = dynamic_cast<FinishLine*>(ptr))
	{
		GameManager::GetInstance()->SetState(GameState::Winning);
	}
}
