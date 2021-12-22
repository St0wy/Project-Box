#pragma once
#include "Entity.h"

/**
 * \brief Represents a block in the world.
 */
class Block final : public Entity
{
public:
	Block(b2World& world, b2Vec2 position);
};
