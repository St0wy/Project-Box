#pragma once
#include <SFML/Graphics.hpp>
#include "TextureType.h"

/**
 * \brief A service to get textures.
 */
class TextureService
{
public:
	~TextureService() = default;

	/**
	 * \brief Loads the textures into memory.
	 */
	void init();

	/**
	 * \brief Gets the requested texture.
	 * \param textureType The "id" of the texture.
	 * \return A pointer to the requested texture.
	 */
	sf::Texture* getTexture(TextureType textureType);
private:
	sf::Texture blockTexture_;
	sf::Texture charSpritesheet_;
};