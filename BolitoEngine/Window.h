#pragma once

#include <string>
#include <SDL/SDL.h>
#include <GL/glew.h>

namespace BolitoEngine {

	enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class Window
	{
	public:
		Window();
		~Window();

		void SwapBuffers();
		int CreateWindow(std::string name, int height, int width, Uint32 windowFlags);
	private:
		SDL_Window* _sdlWindow;
	};
}

