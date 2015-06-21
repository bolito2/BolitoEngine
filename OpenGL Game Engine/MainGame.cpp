#include "MainGame.h"
#include <SDL/SDL.h>
#include <iostream>
#include <string>
#include <GL/glew.h>
#include "Sprite.h"
#include "Errors.h"
#include "GLTexture.h"

#include "ImageLoader.h"

MainGame::MainGame(int width, int height) : 

	time(0.0f),
	_width(width),
	_height(height),
	_window(nullptr),
	_gameState(GameState::PLAY),
	_maxFPS(60.0f)

{

}


MainGame::~MainGame()
{
}

void MainGame::run() {
	initSystems();

	_sprites.push_back(new Sprite());
	_sprites.back()->init(-1.0f, -1.0f, 1.0f , 1.0f , "Textures/PNG/CharacterRight_Standing.png");
	
	_sprites.push_back(new Sprite());
	_sprites.back()->init(-1.0f, 0.0f, 1.0f, 1.0f, "Textures/PNG/CharacterRight_Standing.png");
	
	_sprites.push_back(new Sprite());
	_sprites.back()->init(0.0f, 0.0f, 1.0f, 1.0f, "Textures/PNG/CharacterRight_Standing.png");
	
	_sprites.push_back(new Sprite());
	_sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "Textures/PNG/CharacterRight_Standing.png");
	gameLoop();
}

void MainGame::initSystems() {
	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_OPENGL);

	if (_window == nullptr) {
		fatalError("Window wasn't created :(");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);

	if (glContext == nullptr) {
		fatalError("GLContext wasn't initialized :(");
	}

	GLenum error = glewInit();

	if (error != GLEW_OK) {
		fatalError("Glew wasn't initialised :(");
	}

std:printf("*** OPENGL VERSION : %s *** \n", glGetString(GL_VERSION));

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
//clear
	glClearColor(0.0f, 2.0f, 1.0f, 1.0f);

	SDL_GL_SetSwapInterval(1);

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

	for (int i = 0; i < _sprites.size();i++) {
		_sprites[i]->draw();
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	_shaders.unuse();

	SDL_GL_SwapWindow(_window);
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