#pragma once
#include <SDL/SDL.h>
#include <GL/eglew.h>
#include <vector>
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
	std::vector<Sprite> sprites;
	Shader shader;
	float timer;

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
