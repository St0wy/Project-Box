#include "Ground.h"

#include "VecUtils.h"

Ground::Ground(b2World& world, float groundHalfWidth, float groundHalfHeight, b2Vec2 position)
	: Entity()
{
	// Create ground
	b2BodyDef groundBodyDef;
	groundBodyDef.position = position;
	b2Body* groundBody = world.CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(groundHalfWidth, groundHalfHeight);
	groundBody->CreateFixture(&groundBox, 0.0f);
	body_ = groundBody;

	// Create ground shape
	auto size = sf::Vector2f(groundHalfWidth * 2, groundHalfHeight * 2);
	shape_.setSize(size);
	shape_.setOrigin(size / 2.0f);
	shape_.setPosition(box2dVecToSfml(groundBody->GetWorldCenter()));
	shape_.setFillColor(sf::Color::Green);
}

void Ground::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape_);
}
