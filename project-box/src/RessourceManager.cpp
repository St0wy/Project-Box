#include "RessourceManager.h"
#include <optional>
#include <filesystem>

RessourceManager* RessourceManager::instance_ = nullptr;
std::mutex RessourceManager::mutex_;

RessourceManager* RessourceManager::GetInstance()
{
	std::lock_guard lock(mutex_);
	if (instance_ == nullptr)
	{
		instance_ = new RessourceManager();
	}
	return instance_;
}

std::optional<sf::Texture*> RessourceManager::GetTexture(const std::string& path)
{
	// ReSharper disable once CppTooWideScopeInitStatement
	const auto texture = textures_.find(path);
	if (texture != textures_.end())
	{
		return texture->second.get();
	}
	auto newTexture = std::make_unique<sf::Texture>();
	if (newTexture->loadFromFile(path))
	{
		const auto copy = newTexture.get();
		textures_[path] = std::move(newTexture);
		return copy;
	}
	return {};
}
