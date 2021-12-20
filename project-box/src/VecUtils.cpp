#include <SFML/Graphics.hpp>

#include "VecUtils.h"

sf::Vector2f box2dVecToSfml(const b2Vec2& vector)
{
	return {vector.x, -vector.y};
}

b2Vec2 sfmlVecToBox2d(const sf::Vector2f& vector)
{
	return { vector.x, -vector.y };
}

float magnitude(const b2Vec2& vec)
{
	return std::sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

