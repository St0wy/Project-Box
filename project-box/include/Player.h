#pragma once

#include "Entity.h"
#include "FrameAnimation.h"
#include "PlayerState.h"

class Player final : public Entity
{
private:
	int32 footContactsCounter_;
	PlayerState state_;
	FrameAnimation idle_;
	FrameAnimation walk_;
	float gravity_;
	float jumpVelocity_;
	b2Vec2 moveVel_;
public:
	static constexpr float MOVE_SPEED = 10.0;
	static constexpr float JUMP_HEIGHT = 6.5f;
	static constexpr float TIME_TO_JUMP_APEX = 0.4f;

	explicit Player(b2World& world);
	Player(b2World& world, const b2BodyDef& bodyDef, const b2PolygonShape& collisionShape);

	PlayerState GetState() const;

	b2Vec2 ComputeMovementVec(const sf::Time deltaTime);

	bool IsGrounded() const;

	void Update(sf::Time deltaTime) override;

	void StartContact();
	void EndContact();
};
