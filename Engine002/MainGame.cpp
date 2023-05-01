#include "MainGame.h"

MainGame::MainGame() {
	window = nullptr;
	width = 600;
	height = 600;
	gameState = GameState::PLAY;
	timer = 0.0f;
	timerSpawn = 0.0f;
}

MainGame::~MainGame() {

}

void MainGame::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("poggers engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
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

	timerSpawn += 0.001f;
	if (timerSpawn > 1.0f) {
		timerSpawn = 0.0f;
		size_t index = points.size();
		points.push_back(std::make_pair(cosf(timer) * 0.25f, sinf(timer) * 0.25f));
	}

	timer += 0.001f;

	shader.Use();
	GLint uDesface = shader.getUniform("uDesface");
	GLint uAddPoss = shader.getUniform("uAddPoss");

	for (size_t i = 0; i < points.size(); i++) {
		glUniform1f(uDesface, timer + 0.1f*i);
		glUniform2f(uAddPoss, points[i].first, points[i].second);
		sprite.draw();
	}
	
	SDL_GL_SwapWindow(window);
}

void MainGame::run() {
	init();
	
	sprite.init(-0.5f, -0.5f, 1, 1);

	update();
}

void MainGame::update() {
	while (gameState != GameState::EXIT) {
		draw();
		processInput();
	}
}

