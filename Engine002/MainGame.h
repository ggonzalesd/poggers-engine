#pragma once
#include <SDL/SDL.h>
#include <GL/eglew.h>
#include <vector>
#include <utility>
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
	std::vector<std::pair<GLfloat, GLfloat>> points;
	float timer;
	float timerSpawn;

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
