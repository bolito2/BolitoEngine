#include "Errors.h"
#include <iostream>
#include <SDL\SDL.h>

void fatalError(std::string error) {
	std::cout << error << std::endl;
	system("PAUSE");
	SDL_Quit();
	exit(1);
}