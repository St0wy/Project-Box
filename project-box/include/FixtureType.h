#pragma once

/**
 * \brief Enum used to differentiate fixtures. It is placed in the userData.pointer of the fixture.
 */
enum class FixtureType : std::uintptr_t
{
	None = 0,
	PlayerFootSensor,
	PlayerHeadSensor,
};