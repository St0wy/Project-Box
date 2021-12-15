#pragma once
#include "Frame.h"

#include <vector>

#include <SFML/Graphics/Sprite.hpp>

// Inspired by https://bromeon.ch/libraries/thor/index.html

class FrameAnimation
{
private:
	std::vector<Frame> frames_;
	float duration_;
	float sumFramesDuration_;
	float totalProgress_;
	sf::Sprite& target_;

public:
	explicit FrameAnimation(sf::Sprite& target, float duration);

	void AddFrame(float relativeDuration, const sf::IntRect& subrect);
	void AddFrame(float relativeDuration, const sf::IntRect& subrect, sf::Vector2f origin);
	void Update(float elapsed);
};