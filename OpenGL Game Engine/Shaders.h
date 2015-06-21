#pragma once

#include <string>
#include <GL/glew.h>

class Shaders
{
public:
	Shaders();
	~Shaders();

	void compileShaders(const std::string& vertexShadersPath,const std::string& fragShadersPath);
	void addAtribute(const std::string& atrName);
	void LinkShaders();
	void use();
	void unuse();

	GLint getUniformLocation(const std::string& name);
private:
	void compileShader(const std::string& filePath, GLuint shader);
	int _numAtrs;

	GLuint _vertShader;
	GLuint _fragShader;
	GLuint _program;
};

