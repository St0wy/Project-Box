#include "MathUtils.h"

#include <algorithm>


// Translated from : https://stackoverflow.com/questions/61372498/how-does-mathf-smoothdamp-work-what-is-it-algorithm
float SmoothDamp(const float current, float target, float& currentVelocity, float smoothTime, const sf::Time deltaTime, const float maxSpeed)
{
	// Based on Game Programming Gems 4 Chapter 1.10
	smoothTime = std::max(0.0001f, smoothTime);
	const float omega = 2.0f / smoothTime;

	const float x = omega * deltaTime.asSeconds();
	const float exp = 1.0f / (1.0f + x + 0.48f * x * x + 0.235f * x * x * x);
	float change = current - target;
	const float originalTo = target;

	// Clamp maximum speed
	const float maxChange = maxSpeed * smoothTime;
	change = std::clamp(change, -maxChange, maxChange);
	target = current - change;

	const float temp = (currentVelocity + omega * change) * deltaTime.asSeconds();
	currentVelocity = (currentVelocity - omega * temp) * exp;
	float output = target + (change + temp) * exp;

	// Prevent overshooting
	if (originalTo - current > 0.0f == output > originalTo)
	{
		output = originalTo;
		currentVelocity = (output - originalTo) / deltaTime.asSeconds();
	}

	return output;
}
