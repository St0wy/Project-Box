#include "FinishLine.h"

#include "Locator.h"
#include "Texture/TextureService.h"

FinishLine::FinishLine(b2World& world, const b2Vec2 position)
	: Entity()
{
	// Create body
	b2BodyDef entityBodyDef;
	entityBodyDef.position = position;

	// Add the entity to the body's user data so it can be retrived when a collision happens
	entityBodyDef.userData.pointer = reinterpret_cast<std::uintptr_t>(this);
	body_ = world.CreateBody(&entityBodyDef);

	// Create collision shape
	b2PolygonShape collisionShape;
	collisionShape.SetAsBox(1.0f, 4.9f);

	body_->CreateFixture(&collisionShape, 0.0f);

	// Load and set texture
	TextureService* textureService = Locator::getTextureService();
	const sf::Texture* spritesheetTexture = textureService->getTexture(TextureType::CharSpritesheet);
	setTexture(*spritesheetTexture, sf::IntRect(256, 0, 16, 79));
}
