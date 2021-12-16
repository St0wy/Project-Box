#include "Texture/TextureService.h"
#include "Consts.h"

sf::Texture TextureService::blockTexture_;
sf::Texture TextureService::charSpritesheet_;

void TextureService::init()
{
	blockTexture_.loadFromFile(BLOCK_SPRITE_PATH);
}

sf::Texture* TextureService::getTexture(TextureType textureType)
{
	// TODO Return texture
}
