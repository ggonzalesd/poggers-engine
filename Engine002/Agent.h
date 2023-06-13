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
	glm::vec3 color = glm::vec3(1.0f);
	glm::vec3 position = glm::vec3(0.f);
	float scale = 1.0f;
	float angle = 0.0f;
	float fx = 0.0f;
	float fy = 0.0f;

	Agent(Texture* texture_, const glm::vec3 &position_=glm::vec3(0.f), const glm::vec3 &color_ = glm::vec3(1.0f));
	~Agent();

	void updateModel();

	void Uniform(Shader& shader);
	void Uniform(GLint uModel, GLint uTexture, GLint uColor);

	void Draw(Sprite& sprite);
};

