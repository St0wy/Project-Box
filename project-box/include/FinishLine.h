#pragma once

#include <box2d/box2d.h>
#include "Entity.h"

/**
 * \brief The finish line of the level.
 */
class FinishLine final : public Entity
{
public:
	explicit FinishLine(b2World& world, b2Vec2 position);
};