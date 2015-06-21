#pragma once

#include <string>
#include "GLTexture.h"

class ImageLoader {
public :
	static GLTexture loadImage(std::string path);
};