#include "GameManager.h"
#include "GameState.h"

GameManager* GameManager::instance_ = nullptr;
std::mutex GameManager::mutex_;

GameManager* GameManager::GetInstance()
{
	std::lock_guard lock(mutex_);
	if (instance_ == nullptr)
	{
		instance_ = new GameManager();
	}
	return instance_;
}

GameState GameManager::GetState() const
{
	return state_;
}

void GameManager::SetState(const GameState state)
{
	state_ = state;
}
