#pragma once
#include <SDL/SDL.h>
#include <string>
#include <BolitoEngine/Sprite.h>
#include <BolitoEngine/Shaders.h>
#include <BolitoEngine/ResourceManager.h>
#include <BolitoEngine/GLTexture.h>
#include <BolitoEngine/Window.h>
#include <BolitoEngine/Camera2D.h>
#include <vector>

using namespace BolitoEngine;

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
	GameState _gameState;
	MainGame* _prueba;
	MainGame* _prueba2;

	void CalculateFPS();
	float _fps;
	float _maxFPS;

	MainGame *_subscribed[10];

	std::vector<BolitoEngine::Sprite*> _sprites;

	Shaders _shaders;

	Window _window;

	int _width;
	int _height;

	Camera2D _mainCamera;
};

