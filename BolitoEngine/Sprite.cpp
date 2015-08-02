#include "Sprite.h"

#include <string>

#include "Vertex.h"

#include "ResourceManager.h"

namespace BolitoEngine {

	Sprite::Sprite()
	{
		_vboID = 0;
	}


	Sprite::~Sprite()
	{
		if (_vboID != 0) {
			glDeleteBuffers(1, &_vboID);
		}
	}

	void Sprite::init(float x, float y, float w, float h, std::string filePath)
	{
		_x = x;
		_y = y;
		_w = w;
		_h = h;


		if (_vboID == 0)
		{
			glCreateBuffers(1, &_vboID);
		}

		BolitoEngine::Vertex vertexData[6];

		vertexData[0].setPosition(x + w, y + h);
		vertexData[0].setUV(1.0f, 1.0f);

		vertexData[1].setPosition(x, y + h);
		vertexData[1].setUV(0.0f, 1.0f);

		vertexData[2].setPosition(x, y);
		vertexData[2].setUV(0.0f, 0.0f);

		//Second Triangle
		vertexData[3].setPosition(x, y);
		vertexData[3].setUV(0.0f, 0.0f);

		vertexData[4].setPosition(x + w, y);
		vertexData[4].setUV(1.0f, 0.0f);

		vertexData[5].setPosition(x + w, y + h);
		vertexData[5].setUV(1.0f, 1.0f);

		_texture = ResourceManager::getTexture(filePath);

		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::draw()
	{
		glBindTexture(GL_TEXTURE_2D, _texture.id);

		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		glEnableVertexAttribArray(0);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}