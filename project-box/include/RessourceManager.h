#pragma once
#include <mutex>
#include <map>
#include <string>
#include <SFML/Graphics/Texture.hpp>

class RessourceManager
{
private:
	static RessourceManager* instance_;
	static std::mutex mutex_;
	std::map<std::string, std::unique_ptr<sf::Texture>> textures_;
protected:
	RessourceManager() = default;
public:
	~RessourceManager() = delete;
	RessourceManager(RessourceManager& other) = delete;
	void operator=(const RessourceManager&) = delete;
	RessourceManager(RessourceManager&&) = delete;
	RessourceManager& operator=(RessourceManager&& other) = delete;

	static RessourceManager* GetInstance();
	sf::Texture* GetTexture(const std::string& path);
};
