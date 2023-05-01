#include "MainGame.h"

MainGame::MainGame() {
	window = nullptr;
	width = 600;
	height = 600;
	gameState = GameState::PLAY;
}

MainGame::~MainGame() {

}

void MainGame::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Hola", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		// Validación de fallo
	}
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		// Validación de fallo
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.10f, 0.10f, 0.15f, 1.0f);
	initShader();
}

void MainGame::processInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			break;
		}
	}
}

void MainGame::initShader()
{
	shader = Shader("Shader/vert.glsl", "Shader/frag.glsl", {"aPosition", "aColor"});
}

void MainGame::draw() {
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// si tengo elementos actualizo
	shader.Use();
	sprite.draw();
	SDL_GL_SwapWindow(window);
}

void MainGame::run() {
	init();
	sprite.init(-0.5, -0.5, 1, 1);
	update();
}

void MainGame::update() {
	while (gameState != GameState::EXIT) {
		draw();
		processInput();
	}
}

