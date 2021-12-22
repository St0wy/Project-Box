#include "Entity.h"

#include "Consts.h"
#include "VecUtils.h"

Entity::Entity(b2World& world)
	: world_(world), body_(nullptr)
{
	setScale(SCALE_FACTOR, SCALE_FACTOR);
}

Entity::~Entity()
{
	world_.DestroyBody(body_);
}

b2Body* Entity::getBody() const
{
	return body_;
}

void Entity::update(const sf::Time deltaTime)
{
	setPosition(box2dVecToSfml(body_->GetPosition()));
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite_, states);
}

void Entity::setTexture(const sf::Texture& texture, const sf::IntRect& textureRect)
{
	sprite_.setTextureRect(textureRect);
	this->setTexture(texture);
}

void Entity::setTexture(const sf::Texture& texture)
{
	sprite_.setTexture(texture);
	const sf::IntRect textureRect = sprite_.getTextureRect();
	const float xCenter = static_cast<float>(textureRect.width) / 2.0f;
	const float yCenter = static_cast<float>(textureRect.height) / 2.0f;
	sprite_.setOrigin(xCenter, yCenter);
}

sf::Sprite& Entity::getSprite()
{
	return sprite_;
}
