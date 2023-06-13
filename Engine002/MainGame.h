#pragma once
#include <SDL/SDL.h>
#include <GL/eglew.h>
#include <cmath>
#include "Shader.h"
#include "Sprite.h"
#include "Texture.h"
#include "Camera.h"
#include "Agent.h"
#include "TextureCache.h"

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
	TextureCache textureCache;
	std::vector<Agent> agents;
	Camera camera;
	float timer;
	Uint32 lastTime;
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
