#include "MainGame.h"
#include <time.h>
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

	timer += 0.15f * 3.14f / 60.f;

	camera.update();
	
	// si tengo elementos actualizo
	shader.Use();
	camera.Uniform(shader, "uCamera");
	sprite.Bind();

	for (int i = 0; i<agents.size(); i++) { 
		float angle = atan2f(agents[i].position.y, agents[i].position.x);
		agents[i].fx -= 0.001f * cosf(angle);
		agents[i].fy -= 0.001f * sinf(angle);

		agents[i].scale = 0.25f;
		agents[i].position.x += agents[i].fx;
		agents[i].position.y += agents[i].fy;
		agents[i].angle = cosf(timer + i + agents[i].position.x + agents[i].position.y);

		agents[i].updateModel();
		agents[i].Uniform(shader);
		agents[i].Draw(sprite);
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
	srand(time(NULL));

	sprite.init();

	lastTime = SDL_GetTicks();
	camera = Camera(width, height);

	auto tex01 = textureCache["Images/texture01.png"];
	auto tex02 = textureCache["Images/texture02.png"];
	auto tex03 = textureCache["Images/texture03.png"];
	auto tex04 = textureCache["Images/texture04.png"];

	for (int i = 0; i < 100; i++) {
		switch (rand()%4)
		{
		case 0:
			agents.push_back(Agent(tex01, glm::vec3(0.f), { 1.0f, .0f, 1.f }));
			break;
		case 1:
			agents.push_back(Agent(tex02, glm::vec3(0.f), {1.0f, 1.0f, 0.f}));
			break;
		case 2:
			agents.push_back(Agent(tex03, glm::vec3(0.f), { 0.f, 1.0f, 0.f }));
			break;
		case 3:
			agents.push_back(Agent(tex04));
			break;
		}
	}

	for (Agent& agent : agents) {
		agent.fx = 0.0002f * (float)(rand() % 200 - 100);
		agent.fy = 0.0002f * (float)(rand() % 200 - 100);
		agent.position.x = 0.01f * (float)(rand() % 180 - 90);
		agent.position.y = 0.01f * (float)(rand() % 180 - 90);
	}

	update();
}

void MainGame::update() {
	while (gameState != GameState::EXIT) {
		draw();
		processInput();
	}
}

