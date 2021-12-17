#include "GameManager.h"
#include "GameState.h"

GameState GameManager::getState() const
{
	return state_;
}

void GameManager::setState(const GameState state)
{
	state_ = state;
}
