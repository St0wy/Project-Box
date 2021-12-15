#pragma once
#include <SFML/Graphics/Rect.hpp>

struct Frame
{
	float relativeDuration;
	sf::IntRect subrect;
	sf::Vector2f origin;
	bool applyOrigin;

	Frame(const float duration, const sf::IntRect& subrect)
		: relativeDuration(duration), subrect(subrect), applyOrigin(false)
	{
	}

	Frame(const float duration, const sf::IntRect& subrect, const sf::Vector2f origin)
	: relativeDuration(duration), subrect(subrect), origin(origin), applyOrigin(true)
	{
	}
};
