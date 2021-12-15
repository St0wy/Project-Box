#pragma once
#include <cmath>

#include <SFML/System/Time.hpp>

// Gradually changes a value towards a desired goal over time.
float SmoothDamp(float current,
	float target,
	float& currentVelocity,
	float smoothTime,
	sf::Time deltaTime,
	float maxSpeed = INFINITY);
