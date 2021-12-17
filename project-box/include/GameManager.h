#pragma once
#include "GameState.h"

class GameManager
{
private:
	GameState state_ = GameState::Playing;
public:
	[[nodiscard]] GameState getState() const;
	void setState(GameState state);
};
