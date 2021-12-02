#include "Entity.h"
#include "VecUtils.h"

Entity::Entity() : body_(nullptr)
{
}

Entity::Entity(b2World& world)
{
	// Create body
	b2BodyDef entityBodyDef;
	entityBodyDef.type = b2_dynamicBody;
	entityBodyDef.position.Set(0.0f, 0.0f);
	// Add the entity to the body's user data so it can be retrived when a collision happens
	entityBodyDef.userData.pointer = reinterpret_cast<std::uintptr_t>(this);
	body_ = world.CreateBody(&entityBodyDef);

	// Create collision shape
	b2PolygonShape collisionShape;
	collisionShape.SetAsBox(1.0f, 1.0f);

	// Create fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &collisionShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body_->CreateFixture(&fixtureDef);
}

Entity::Entity(b2World& world, const b2BodyDef& bodyDef, const b2PolygonShape& collisionShape)
	:body_(world.CreateBody(&bodyDef))
{
	// Create fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &collisionShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.0f;

	body_->CreateFixture(&fixtureDef);
}

b2Body* Entity::GetBody() const
{
	return body_;
}

void Entity::SetBody(b2Body* body)
{
	body_ = body;
}

void Entity::Update(const sf::Time deltaTime)
{
	setPosition(Box2dVecToSfml(body_->GetPosition()));
}

void Entity::SetTexture(const sf::Texture& texture, const sf::IntRect& textureRect)
{
	setTextureRect(textureRect);
	this->SetTexture(texture);
}

void Entity::SetTexture(const sf::Texture& texture)
{
	setTexture(texture);

	const sf::Vector2f size(texture.getSize());
	const sf::Vector2f center = size / 2.0f;
	setOrigin(center);
}
