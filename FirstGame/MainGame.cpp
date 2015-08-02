#include "MainGame.h"
#include <SDL/SDL.h>
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <BolitoEngine/Sprite.h>
#include <BolitoEngine/Errors.h>
#include <BolitoEngine/GLTexture.h>
#include <BolitoEngine/ImageLoader.h>

MainGame::MainGame(int width, int height) : 

	time(0.0f),
	_width(width),
	_height(height),
	_gameState(GameState::PLAY),
	_maxFPS(60.0f)

{
	_mainCamera.init(width, height);
}


MainGame::~MainGame()
{
}

void MainGame::run() {
	

	
	initSystems();

	_sprites.push_back(new BolitoEngine::Sprite());
	_sprites.back()->init(0.0f, 0.0f, _width/2 , _height/2, "Textures/PNG/CharacterRight_Standing.png");
	
	_sprites.push_back(new BolitoEngine::Sprite());
	_sprites.back()->init(_width/2, 0.0f, _width / 2, _height / 2, "Textures/PNG/CharacterRight_Standing.png");
	
	//_sprites.push_back(new BolitoEngine::Sprite());
	//_sprites.back()->init(0.0f, 0.0f, 1.0f, 1.0f, "Textures/PNG/CharacterRight_Standing.png");
	
	//_sprites.push_back(new BolitoEngine::Sprite());
	//_sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "Textures/PNG/CharacterRight_Standing.png");
	gameLoop();
}

void MainGame::initSystems() {

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	_window.CreateWindow("LOLXD", _height, _width, 0);

	initShaders();
}

void MainGame::initShaders() {
	_shaders.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_shaders.addAtribute("vertexPosition");
	_shaders.addAtribute("vertexColor");
	_shaders.addAtribute("vertexUV");
	_shaders.LinkShaders();
}

void MainGame::gameLoop() {
	while (_gameState == GameState::PLAY) {
		
		float startTicks = SDL_GetTicks();

		time += 0.01f;

		CalculateFPS();
		static int frameCounter = 0;
		if (frameCounter == 10) 
		{
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}
		frameCounter++;
		processInput();

		_mainCamera.Update();

		draw();

		float currentTicks = SDL_GetTicks() - startTicks;

		/*
		if (1000.0f / _maxFPS < currentTicks) {
			SDL_Delay(1000.0f / _maxFPS - currentTicks);
		}
		*/

	}
}

void MainGame::processInput() {
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::STOP;
			break;
		case SDL_KEYDOWN:
			switch (evnt.key.keysym.sym)
			{
			case SDLK_w :
				_mainCamera.setPosition(_mainCamera.getPosition() + glm::vec2(0.0, 10.0));
				break;
			case SDLK_a:
				_mainCamera.setPosition(_mainCamera.getPosition() + glm::vec2(10.0, 0.0));
				break;
			case SDLK_s:
				_mainCamera.setPosition(_mainCamera.getPosition() + glm::vec2(0.0, -10.0));
				break;
			case SDLK_d:
				_mainCamera.setPosition(_mainCamera.getPosition() + glm::vec2(-10.0, 0.0));
				break;
			}
			break;
		}
	}
}

void MainGame::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shaders.use();
	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = _shaders.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	//GLint timeLocation = _shaders.getUniformLocation("time");
	//glUniform1f(timeLocation, time);

	GLint matrixLocation = _shaders.getUniformLocation("P");
	glm::mat4 cameraMat = _mainCamera.getCameraMatrix();
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE,&(cameraMat[0][0]));

	for (int i = 0; i < _sprites.size();i++) {
		_sprites[i]->draw();
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	_shaders.unuse();

	_window.SwapBuffers();
}
void MainGame::CalculateFPS()
{
	static const int NUM_LENGHT = 10;
	static float frameTimes[NUM_LENGHT];
	static int currentFrame;

	static float previousTicks = SDL_GetTicks();
	float currentTicks = SDL_GetTicks();

	float frameTime = currentTicks - previousTicks;

	previousTicks = currentTicks;

	frameTimes[currentFrame % NUM_LENGHT] = frameTime;

	int count;

	currentFrame++;
	
	if (currentFrame < NUM_LENGHT) 
	{
		count = currentFrame;
	}
	else 
	{
		count = NUM_LENGHT;
	}
	float frameTimeAverage = 0.0f;
	for (int i = 0; i < count;i++) 
	{
		frameTimeAverage += frameTimes[i];
	}
	if (count != 0)
	{
		frameTimeAverage /= count;

		_fps = 1000.0f / frameTimeAverage;
	}
	else
		_fps = 60.0f;
}

MainGame::MainGame() {}