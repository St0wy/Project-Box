#include "FinishLine.h"

#include "Consts.h"
#include "RessourceManager.h"

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
	const std::optional<sf::Texture*> texture =
		RessourceManager::GetInstance()->GetTexture(SPRITESHEET_PATH);
	const sf::Texture* blockTexture = texture.value();
	SetTexture(*blockTexture, sf::IntRect(256, 0, 16, 79));
}
