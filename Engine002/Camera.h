#pragma once

#include <string>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

class Camera
{
private:
	float screenWidth;
	float screenHeight;
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 matrix;
public:
	glm::vec3 position;

	Camera();
	Camera(float screenWidth, float screenHeight);
	~Camera();

	void Uniform(GLint loc);
	void Uniform(Shader& shader, std::string name);

	void update();
};

