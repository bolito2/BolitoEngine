#include <SDL/SDL.h>
#include "MainGame.h"
#include <iostream>

int wmain(int argc,wchar_t* argv[]) {

	int width;
	int height;

	std::cout << "Introduce el alto de la ventana : ";
	std::cin >> height;

	std::cout << "Introduce el ancho de la ventana : ";
	std::cin >> width;

	MainGame maingame(width, height);
	maingame.run();
	return 0;
}