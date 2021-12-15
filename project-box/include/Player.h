#pragma once

#include "Entity.h"
#include "FrameAnimation.h"
#include "PlayerState.h"

class Player final : public Entity
{
private:
	bool isFacingRight_;
	int32 moveDirection_;
	int32 footContactsCounter_;
	PlayerState state_;
	FrameAnimation idle_;
	FrameAnimation walk_;
public:
	static constexpr float MAX_SPEED = 5.4f;
	static constexpr float JUMP_HEIGHT = 17.0f;
	static constexpr float JUMP_BOOST = 1.2f;

	explicit Player(b2World& world);
	Player(b2World& world, const b2BodyDef& bodyDef, const b2PolygonShape& collisionShape);

	PlayerState GetState() const;

	b2Vec2 ComputeMovementVec();

	bool IsGrounded() const;

	void Update(sf::Time deltaTime) override;

	void StartContact();
	void EndContact();
};
