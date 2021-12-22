#pragma once

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

/**
 * \brief Converts a box2d vector to an SFML vector.
 * \param vector The vector to be converted.
 * \return A vector with a flipped y axis.
 */
sf::Vector2f box2dVecToSfml(const b2Vec2& vector);

/**
 * \brief Converts an SFML vector to a box3d vector.
 * \param vector The vector to be converted.
 * \return A vector with a flipped y axis.
 */
b2Vec2 sfmlVecToBox2d(const sf::Vector2f& vector);

/**
 * \brief Normalises the provided vector.
 * \tparam T Number type of the vector.
 * \param vec Vector to normalize.
 */
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

/**
 * \brief Gets the magnitude of the vector.
 * \tparam T Number type of the vector.
 * \param vec The vector to get the magnitude from.
 * \return The length of the vector.
 */
template<typename T>
T magnitude(const sf::Vector2<T>& vec)
{
	return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

/**
 * \brief Gets the magnitude of the vector.
 * \param vec The vector to get the magnitude from.
 * \return The length of the vector.
 */
float magnitude(const b2Vec2& vec);