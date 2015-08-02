#include "Camera2D.h"
#include <iostream>

namespace BolitoEngine
{
	void BolitoEngine::Camera2D::init(int width, int height)
	{
		_orthoMatrix = glm::ortho ( 0.0f, (float)height, 0.0f, (float)width);
	}

	void Camera2D::Update() 
	{
		if (_needsMatrixTransform) {
			std::cout << _position.x;
			std::cout << " ";
			std::cout << _position.y << std::endl;

			glm::vec3 translate(-_position.x, -_position.y, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);
			glm::vec3 scaleFactor(_scale, _scale, 0.0f);
			_cameraMatrix = glm::scale(_orthoMatrix, scaleFactor);
			_needsMatrixTransform = false;

			std::cout << _position.x;
			std::cout << " ";
			std::cout << _position.y << std::endl;
		}
	}

	Camera2D::Camera2D() : _needsMatrixTransform(true), _scale(1.0f), _cameraMatrix(1.0f), _orthoMatrix(1.0f)
	{
	}


	Camera2D::~Camera2D()
	{
	}
}