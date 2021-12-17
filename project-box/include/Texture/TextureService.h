#pragma once
#include <SFML/Graphics.hpp>
#include "TextureType.h"

class TextureService
{
public:
	~TextureService() = default;
	void init();
	sf::Texture* getTexture(TextureType textureType);
private:
	sf::Texture blockTexture_;
	sf::Texture charSpritesheet_;
};