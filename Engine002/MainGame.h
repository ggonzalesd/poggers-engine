#pragma once
#include <SDL/SDL.h>
#include <GL/eglew.h>
#include "Shader.h"
#include "Sprite.h"

enum class GameState {
	PLAY, EXIT
};

class MainGame {

private:
	int width;
	int height;
	SDL_Window* window;
	Sprite sprite;
	Shader shader;
	void init();
	void processInput();
	void initShader();

public:
	MainGame();
	~MainGame();
	GameState gameState;
	void run();
	void draw();
	void update();
};
