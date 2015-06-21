#include <string>
#include <vector>

#include "picoPNG.h"
#include "GLTexture.h"
#include "ImageLoader.h"
#include "IOManager.h"

#include "Errors.h"


#include <iostream>

	GLTexture ImageLoader::loadImage(std::string path) {

		GLTexture texture = {};
		unsigned long height, width;

		std::vector<unsigned char> in, out;

		if (IOManager::readFile(path, in) == false) {
			fatalError("Failed to read texture file :(");
		}

		int error = decodePNG(out, width, height, &(in[0]), in.size());
		if(error != 0){
			fatalError("Failed to decode the png at " + path);
		}

		glGenTextures(1, &(texture.id));
		glBindTexture(GL_TEXTURE_2D, texture.id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		texture.width = width;
		texture.height = height;

		return texture;
	}
