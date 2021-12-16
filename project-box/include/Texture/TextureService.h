#pragma once
#include <SFML/Graphics.hpp>
#include "TextureType.h"

class TextureService
{
public:
	~TextureService() = default;
	static void init();
	static sf::Texture* getTexture(TextureType textureType);
private:
	static sf::Texture blockTexture_;
	static sf::Texture charSpritesheet_;
};