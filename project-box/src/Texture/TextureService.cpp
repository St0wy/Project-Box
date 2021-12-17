#include "Texture/TextureService.h"
#include "Consts.h"

void TextureService::init()
{
	blockTexture_.loadFromFile(BLOCK_SPRITE_PATH);
	charSpritesheet_.loadFromFile(SPRITESHEET_PATH);
}

sf::Texture* TextureService::getTexture(const TextureType textureType)
{
	switch (textureType) {
	case TextureType::CharSpritesheet:
		return &charSpritesheet_;
	default:  // NOLINT(clang-diagnostic-covered-switch-default)
	case TextureType::Block:
		return &blockTexture_;
	}
}
