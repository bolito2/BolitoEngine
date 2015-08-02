#include "Shaders.h"
#include "Errors.h"

#include <vector>

#include <fstream>

namespace BolitoEngine {

	Shaders::Shaders()
	{
		_numAtrs = 0;
		_program = 0;
		_vertShader = 0;
		_fragShader = 0;
	}

	Shaders::~Shaders()
	{
	}

	void Shaders::compileShaders(const std::string& vertexShadersPath, const std::string& fragShadersPath)
	{

		_program = glCreateProgram();

		_vertShader = glCreateShader(GL_VERTEX_SHADER);

		if (_vertShader == 0) {
			fatalError("Cannot create vertex file");
		}

		compileShader(vertexShadersPath, _vertShader);

		_fragShader = glCreateShader(GL_FRAGMENT_SHADER);

		if (_fragShader == 0) {
			fatalError("Cannot create fragment file");
		}

		compileShader(fragShadersPath, _fragShader);
	}

	void Shaders::compileShader(const std::string& filePath, GLuint shader)
	{
		std::fstream shaderFile(filePath);
		if (shaderFile.fail()) {
			perror(filePath.c_str());
			fatalError("Unable to locate vertex shaders at " + filePath);
		}

		std::string document = "";
		std::string line;

		while (std::getline(shaderFile, line)) {
			document += line + "\n";
		}

		shaderFile.close();

		const char* textToPtr = document.c_str();

		glShaderSource(shader, 1, &textToPtr, nullptr);

		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

			// Provide the infolog in whatever manor you deem best.
			// Exit with failure.
			glDeleteShader(shader); // Don't leak the shader.
			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shader " + filePath + " failed to compile");

		}
	}

	void Shaders::LinkShaders() {

		glAttachShader(_program, _vertShader);
		glAttachShader(_program, _fragShader);

		glLinkProgram(_program);

		glDetachShader(_program, _vertShader);
		glDetachShader(_program, _fragShader);
		glDeleteShader(_vertShader);
		glDeleteShader(_fragShader);
	}

	void Shaders::addAtribute(const std::string& atrName) {
		glBindAttribLocation(_program, _numAtrs++, atrName.c_str());
	}

	void Shaders::use() {
		glUseProgram(_program);
		for (int i = 0; i < _numAtrs; i++) {
			glEnableVertexAttribArray(i);
		}
	}
	void Shaders::unuse() {
		glUseProgram(0);
		for (int i = 0; i < _numAtrs; i++) {
			glDisableVertexAttribArray(i);
		}
	}

	GLint Shaders::getUniformLocation(const std::string & name)
	{
		GLint location = glGetUniformLocation(_program, name.c_str());
		if (location == GL_INVALID_INDEX) {
			fatalError(name + " uniform wasn't found");
			return NULL;
		}
		else return location;
	}
}