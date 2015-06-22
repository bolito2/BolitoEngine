#include "TextureCache.h"
#include <map>
#include "ImageLoader.h"

#include <iostream>

TextureCache::TextureCache()
{
}


TextureCache::~TextureCache()
{
}

GLTexture TextureCache::getTexture(std::string texturePath)
{
	auto mit = _textureMap.find(texturePath);

	if (mit == _textureMap.end()) 
	{
		GLTexture texture = ImageLoader::loadImage(texturePath);

		_textureMap.insert(make_pair(texturePath, texture));

		std::cout << "Created texture." << std::endl;

		return texture;
	}
	std::cout << "Loaded existing texture." << std::endl;
	return mit->second;
}
