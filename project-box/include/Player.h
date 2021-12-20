#pragma once

#include "Entity.h"
#include "FrameAnimation.h"
#include "PlayerState.h"

class Player final : public Entity
{

public:
	static constexpr float MOVE_SPEED = 10.0;
	static constexpr float JUMP_HEIGHT = 6.5f;
	static constexpr float TIME_TO_JUMP_APEX = 0.4f;
	static constexpr float ACCELERATION_TIME_AIRBORNE = 0.2f;
	static constexpr float ACCELERATION_TIME_GROUNDED = 0.1f;

	explicit Player(b2World& world);
	PlayerState getState() const;
	b2Vec2 computeMovementVec(const sf::Time deltaTime);
	void update(sf::Time deltaTime) override;
	bool isGrounded() const;
	bool isTouchingHead() const;
	void startFootContact();
	void endFootContact();
	void startHeadContact();
	void endHeadContact();
private:
	int32 footContactsCounter_;
	int32 headContactsCounter_;
	PlayerState state_;
	FrameAnimation idle_;
	FrameAnimation walk_;
	bool oldIsInputingJump_;
	float gravity_;
	float jumpVelocity_;
	b2Vec2 moveVel_;
};
