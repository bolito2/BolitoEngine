#pragma once
#include <GL/glew.h>
#include "Sprite.h"
#include <string>
#include <cstddef>

#include "GLTexture.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float x, float y, float w, float h, std::string filePath);

	void draw();

private:
	GLTexture _texture;
	GLuint _vboID;
	float _x, _y, _w, _h;

};

