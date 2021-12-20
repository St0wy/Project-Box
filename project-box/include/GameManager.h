#pragma once
#include "GameState.h"

class GameManager
{
public:
	[[nodiscard]] GameState getState() const;
	void setState(GameState state);
private:
	GameState state_ = GameState::Playing;
};
