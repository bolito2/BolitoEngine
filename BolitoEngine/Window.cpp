#include "Window.h"
#include "Errors.h"

namespace BolitoEngine {

	Window::Window() :_sdlWindow(nullptr)
	{

	}

	void Window::SwapBuffers()
	{
		SDL_GL_SwapWindow(_sdlWindow);
	}

	int Window::CreateWindow(std::string name, int height, int width, Uint32 windowFlags)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;

		if (windowFlags & INVISIBLE)
		{
			flags |= SDL_WINDOW_HIDDEN;
		}

		if (windowFlags & FULLSCREEN)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		if (windowFlags & BORDERLESS)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		_sdlWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, height, width, flags);

		if (_sdlWindow == nullptr) {
			fatalError("Window wasn't created :(");
		}

		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);

		if (glContext == nullptr) {
			fatalError("GLContext wasn't initialized :(");
		}

		GLenum error = glewInit();

		if (error != GLEW_OK) {
			fatalError("Glew wasn't initialised :(");
		}

		std::printf("*** OPENGL VERSION : %s *** \n", glGetString(GL_VERSION));

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		//clear
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		SDL_GL_SetSwapInterval(1);

		return 0;
	}

	Window::~Window()
	{
	}

}