#pragma once
#include "Sprite.h"
#include "Shader.h"
#include "Texture.h"
#include <glm/gtc/type_ptr.hpp>

class Agent
{
private:
	glm::mat4 model = glm::mat4(1.0f);
	Texture* texture = nullptr;

public:
	glm::vec3 position = glm::vec3(0.f);
	float scale = 1.0f;
	float angle = 0.0f;

	Agent(Texture* texture_);
	~Agent();

	void updateModel();

	void Uniform(Shader& shader);
	void Uniform(GLint uModel, GLint uTexture);

	void Draw(Sprite& sprite);
};

