#pragma once
#include <SFML/Graphics/Rect.hpp>

/**
 * \brief Represents a frame in an animation.
 */
struct Frame
{
	/**
	 * \brief The relative duration of the frame. Relative to the total duration of the FrameAnimation.
	 */
	float relativeDuration;

	// The subrect of that frame.
	sf::IntRect subrect;

	/**
	 * \brief The origin of the rect.
	 */
	sf::Vector2f origin;

	/**
	 * \brief Boolean that says if the origin should be applied.
	 */
	bool applyOrigin;

	/**
	 * \brief Creates a new frame.
	 * \param duration The relative duration of the frame.
	 * \param subrect The sub rect of that frame.
	 */
	Frame(const float duration, const sf::IntRect& subrect)
		: relativeDuration(duration), subrect(subrect), applyOrigin(false)
	{
	}

	/**
	 * \brief Creates a new frame.
	 * \param duration The relative duration of the frame.
	 * \param subrect The sub rect of that frame.
	 * \param origin The origin of that frame.
	 */
	Frame(const float duration, const sf::IntRect& subrect, const sf::Vector2f origin)
		: relativeDuration(duration), subrect(subrect), origin(origin), applyOrigin(true)
	{
	}
};
