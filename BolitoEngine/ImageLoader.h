#pragma once

#include <string>
#include "GLTexture.h"

namespace BolitoEngine {

	class ImageLoader {
	public:
		static GLTexture loadImage(std::string path);
	};

}