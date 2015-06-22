#include "ResourceManager.h"

TextureCache ResourceManager::_textureCache;

GLTexture ResourceManager::getTexture(std::string filePath)
{
	return _textureCache.getTexture(filePath);
}
