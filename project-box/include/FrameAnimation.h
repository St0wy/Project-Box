#pragma once
#include "Frame.h"

#include <vector>
#include <SFML/Graphics/Sprite.hpp>

/**
 * \brief Represents an animation.
 * \remarks Inspired by https://bromeon.ch/libraries/thor/index.html
 */
class FrameAnimation
{
public:
	/**
	 * \brief Creates a new FrameAnimation.
	 * \param target The sprite sheet of that animation.
	 * \param duration The total duration (in second) of that animation.
	 */
	FrameAnimation(sf::Sprite& target, float duration);

	/**
	 * \brief Adds a new frame to that animation.
	 * \param relativeDuration The relative duration of that frame.
	 * \param subrect The sub rect of that frame.
	 */
	void addFrame(float relativeDuration, const sf::IntRect& subrect);

	/**
	 * \brief Adds a new frame to that animation.
	 * \param relativeDuration The relative duration of that frame.
	 * \param subrect The sub rect of that frame.
	 * \param origin The origin of that frame.
	 */
	void addFrame(float relativeDuration, const sf::IntRect& subrect, sf::Vector2f origin);

	/**
	 * \brief Updates the animation.
	 * \param elapsed The elapsed time since the last frame in second.
	 */
	void update(float elapsed);

private:
	std::vector<Frame> frames_;
	float duration_;
	float sumFramesDuration_;
	float totalProgress_;
	sf::Sprite& target_;
};