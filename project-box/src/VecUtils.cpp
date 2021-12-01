#include <SFML/Graphics.hpp>

#include "VecUtils.h"

sf::Vector2f Box2dVecToSfml(const b2Vec2& vector)
{
	return {vector.x, -vector.y};
}