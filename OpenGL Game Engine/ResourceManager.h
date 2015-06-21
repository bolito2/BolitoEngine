#pragma once

#include "TextureCache.h"

#include <string>

class ResourceManager
{
public:
	static GLTexture getTexture(std::string filePath);
private:
	static TextureCache _textureCache;
};

