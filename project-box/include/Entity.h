#pragma once

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

class Entity
	: public sf::Sprite
{
private:
	b2Body* body_;
public:
	Entity();
	explicit Entity(b2World& world);
	Entity(b2World& world, const b2BodyDef& bodyDef, const b2PolygonShape& collisionShape);

	b2Body* GetBody() const;
	void SetBody(b2Body* body);

	virtual void Update(sf::Time deltaTime);

	void SetTexture(const sf::Texture& texture, const sf::IntRect& textureRect);
	void SetTexture(const sf::Texture& texture);
};