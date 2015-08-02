#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

namespace BolitoEngine
{

	class Camera2D
	{
	public:
		void init(int width, int height);
		void Update();

		void setPosition(glm::vec2 newPos) {_position = newPos; _needsMatrixTransform= true;}
		glm::vec2 getPosition() { return _position; }

		void setScale(float newScale) {	_scale = newScale; _needsMatrixTransform = true;}

		glm::mat4 getCameraMatrix() { return _cameraMatrix; }

		Camera2D();
		~Camera2D();
	private:
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;
		bool _needsMatrixTransform;
		glm::vec2 _position;
		float _scale;
	};

}