#include "Block.h"

#include "Locator.h"

Block::Block(b2World& world, const b2Vec2 position)
{
	// Create body
	b2BodyDef entityBodyDef;
	entityBodyDef.position = position;

	// Add the entity to the body's user data so it can be retrived when a collision happens
	entityBodyDef.userData.pointer = reinterpret_cast<std::uintptr_t>(this);
	body_ = world.CreateBody(&entityBodyDef);

	// Create collision shape
	b2PolygonShape collisionShape;
	collisionShape.SetAsBox(1.0f, 1.0f);

	body_->CreateFixture(&collisionShape, 0.0f);

	const auto textureService = Locator::getTextureService();

	// Load and set texture
	if (const sf::Texture* texture = textureService->getTexture(TextureType::Block))
	{
		setTexture(*texture);
	}
}
