#include "Player.h"

#include "Consts.h"
#include "VecUtils.h"
#include "FixtureType.h"
#include "RessourceManager.h"

Player::Player(b2World& world)
	:Entity(),
	footContactsCounter_(0),
	state_(PlayerState::Idle),
	idle_(GetSprite(), 0.6f),
	walk_(GetSprite(), 0.6f),
	velocityXSmoothing_(0)
{
	b2BodyDef entityBodyDef;
	entityBodyDef.type = b2_dynamicBody;
	entityBodyDef.position.Set(0.0f, 10.0f);
	entityBodyDef.userData.pointer = reinterpret_cast<std::uintptr_t>(this);
	// Removed gravity because i use one that I compute from JUMP_HEIGHT and TIME_TO_JUMP_APEX
	entityBodyDef.gravityScale = 0.0f;
	entityBodyDef.fixedRotation = true;

	b2PolygonShape collisionShape;
	collisionShape.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &collisionShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	SetBody(world.CreateBody(&entityBodyDef));
	GetBody()->CreateFixture(&fixtureDef);

	b2PolygonShape footPolygonShape;
	footPolygonShape.SetAsBox(0.99f, 0.1f, b2Vec2(0, -1), 0);

	b2FixtureDef footFixtureDef;
	footFixtureDef.isSensor = true;
	constexpr auto sensorPtr = static_cast<uintptr_t>(FixtureType::PlayerFootSensor);
	footFixtureDef.userData.pointer = sensorPtr;
	footFixtureDef.shape = &footPolygonShape;
	GetBody()->CreateFixture(&footFixtureDef);

	for (int i = 0; i < 6; ++i)
	{
		const int x = i * static_cast<int>(SPRITE_SIZE.x);
		idle_.AddFrame(1.0f,
			sf::IntRect(sf::Vector2i(x, 80), sf::Vector2i(SPRITE_SIZE)));
		walk_.AddFrame(1.0f,
			sf::IntRect(sf::Vector2i(x, 80 + static_cast<int>(SPRITE_SIZE.y)), sf::Vector2i(SPRITE_SIZE)));
	}

	const auto playerTextureResult = RessourceManager::GetInstance()->GetTexture(SPRITESHEET_PATH);
	const sf::Texture* playerTexture = playerTextureResult.value();
	SetTexture(*playerTexture, sf::IntRect(0, 80, 16, 16));

	gravity_ = -(2 * JUMP_HEIGHT) / (TIME_TO_JUMP_APEX * TIME_TO_JUMP_APEX);
	jumpVelocity_ = std::abs(gravity_) * TIME_TO_JUMP_APEX;
}

PlayerState Player::GetState() const
{
	return state_;
}

b2Vec2 Player::ComputeMovementVec(const sf::Time deltaTime)
{
	const bool isInputingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	const bool isInputingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	const bool isInputingJump = sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	// Get direction float
	float moveDirection = 0;
	if (isInputingLeft)
		moveDirection = -1;
	if (isInputingRight)
		moveDirection = 1;

	if (IsGrounded())
	{
		moveVel_.y = 0;
	}

	// Jumping
	if (isInputingJump && IsGrounded())
	{
		moveVel_.y = jumpVelocity_;
	}
	moveVel_.x = moveDirection * MOVE_SPEED;
	moveVel_.y += gravity_ * deltaTime.asSeconds();

	//vel *= deltaTime.asSeconds();

	return moveVel_;
}

bool Player::IsGrounded() const
{
	return footContactsCounter_ > 0;
}

void Player::Update(const sf::Time deltaTime)
{
	const b2Vec2 vel = ComputeMovementVec(deltaTime);

	if (vel.x == 0 || !IsGrounded()) {  // NOLINT(clang-diagnostic-float-equal)
		state_ = PlayerState::Idle;
	}
	else
	{
		state_ = PlayerState::Walk;
	}

	const sf::Vector2f scale = getScale();
	if (vel.x > 0)
	{
		setScale(std::abs(scale.x), scale.y);
	}
	else if (vel.x < 0)
	{
		setScale(-std::abs(scale.x), scale.y);
	}

	// Apply move to body
	GetBody()->SetLinearVelocity(vel);

	switch (GetState())
	{
	case PlayerState::Idle:
		idle_.Update(deltaTime.asSeconds());
		break;
	case PlayerState::Walk:
		walk_.Update(deltaTime.asSeconds());
		break;
	}

	Entity::Update(deltaTime);
}

void Player::StartContact()
{
	footContactsCounter_ += 1;
}

void Player::EndContact()
{
	footContactsCounter_ -= 1;
}
