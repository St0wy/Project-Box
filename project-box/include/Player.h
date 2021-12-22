#pragma once

#include "Entity.h"
#include "FrameAnimation.h"
#include "PlayerState.h"

/**
 * \brief The class of the player.
 */
class Player final : public Entity
{
public:
	/**
	 * \brief The movement speed of the player.
	 */
	static constexpr float MOVE_SPEED = 10.0;

	/**
	 * \brief The jump height of the player.
	 */
	static constexpr float JUMP_HEIGHT = 6.5f;

	/**
	 * \brief The time it should take for the player to be at the apex of his jump.
	 */
	static constexpr float TIME_TO_JUMP_APEX = 0.4f;

	/**
	 * \brief Creates a player.
	 * \param world The world where the player is created.
	 */
	explicit Player(b2World& world);

	/**
	 * \brief Gets the state of the player.
	 * \return The state of the player.
	 */
	PlayerState getState() const;

	/**
	 * \brief Computes the movement vector.
	 * \param deltaTime The time elapsed since the last frame.
	 * \return The movement vector.
	 */
	b2Vec2 computeMovementVec(const sf::Time deltaTime);

	void update(sf::Time deltaTime) override;

	/**
	 * \brief Checks if the player is touching the ground.
	 * \return True if the player is grounded.
	 */
	bool isGrounded() const;

	/**
	 * \brief Checks if something is touching the head of the player.
	 * \return True if something is touching the head of the player.
	 */
	bool isTouchingHead() const;

	/**
	 * \brief Increments the counter for the foot contacts.
	 */
	void startFootContact();

	/**
	 * \brief Decrements the counter for the foot contacts.
	 */
	void endFootContact();

	/**
	 * \brief Increments the counter for the head contacts.
	 */
	void startHeadContact();

	/**
	 * \brief Decrements the counter for the head contacts.
	 */
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
