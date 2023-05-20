#include "MainGame.h"
#include <glm/gtc/type_ptr.hpp>

MainGame::MainGame() {
	window = nullptr;
	width = 600;
	height = 600;
	gameState = GameState::PLAY;
	timer = 0.f;
	lastTime = 0;
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
	shader = Shader("Shader/vert.glsl", "Shader/frag.glsl", {"aPosition", "aColor", "aUV"});
}

void MainGame::draw() {

	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	timer += 0.2f * 3.14f / 60.f;
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::rotate(model, timer, glm::vec3(0.f, 0.f, 1.0f));

	camera.update();
	
	// si tengo elementos actualizo
	shader.Use();
	camera.Uniform(shader, "uCamera");
	sprite.Bind();

	for (int i = 0; i<agents.size(); i++) { 

		agents[0].scale = 0.5f;
		agents[0].position.x = 0.75f * cosf(timer+i);
		agents[0].position.y = 0.75f * sinf(timer+i);

		agents[0].updateModel();
		agents[0].Uniform(shader);
		agents[0].Draw(sprite);
	}
	
	sprite.Unbind();
	
	{
		Uint32 deltaTime = SDL_GetTicks() - lastTime;
		if (deltaTime < 11)
			SDL_Delay(11 - deltaTime);
		lastTime = SDL_GetTicks();
		SDL_GL_SwapWindow(window);
	}
}

void MainGame::run() {
	init();

	sprite.init();
	texture = Texture("Images/texture03.png", true);

	lastTime = SDL_GetTicks();
	camera = Camera(width, height);

	agents = {
		Agent(&texture),
		Agent(&texture),
		Agent(&texture),
		Agent(&texture)
	};

	update();
}

void MainGame::update() {
	while (gameState != GameState::EXIT) {
		draw();
		processInput();
	}
}

