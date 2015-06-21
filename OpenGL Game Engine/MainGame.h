#pragma once
#include <SDL/SDL.h>
#include <string>
#include "Sprite.h"
#include "Shaders.h"
#include "ResourceManager.h"
#include "GLTexture.h"

#include <vector>

enum class GameState { PLAY, STOP };

class MainGame
{
public:
	MainGame(int withd, int height);
	MainGame();
	~MainGame();

	void run();

	float time;
private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void draw();
	SDL_Window* _window;
	GameState _gameState;
	MainGame* _prueba;
	MainGame* _prueba2;

	void CalculateFPS();
	float _fps;
	float _maxFPS;

	MainGame *_subscribed[10];

	std::vector<Sprite*> _sprites;

	Shaders _shaders;

	int _width;
	int _height;
};

