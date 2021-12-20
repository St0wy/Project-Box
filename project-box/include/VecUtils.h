#pragma once

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

sf::Vector2f box2dVecToSfml(const b2Vec2& vector);
b2Vec2 sfmlVecToBox2d(const sf::Vector2f& vector);

template<typename T>
void normalize(sf::Vector2<T>& vec)
{
	if (vec.x == 0 && vec.y == 0)
		return;

	T length = Magnitude<T>(vec);

	if (length != 0.0)
	{
		vec /= length;
	}
}

template<typename T>
T magnitude(const sf::Vector2<T>& vec)
{
	return std::sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

float magnitude(const b2Vec2& vec);