#pragma once
#include <mutex>
#include "GameState.h"

class GameManager
{
private:
	static GameManager* instance_;
	static std::mutex mutex_;
	GameState state_ = GameState::Playing;
protected:
	GameManager() = default;
public:
	~GameManager() = delete;
	GameManager(GameManager& other) = delete;
	void operator=(const GameManager&) = delete;
	GameManager(GameManager&&) = delete;
	GameManager& operator=(GameManager&& other) = delete;

	static GameManager* GetInstance();

	[[nodiscard]] GameState GetState() const;
	void SetState(GameState state);
};
