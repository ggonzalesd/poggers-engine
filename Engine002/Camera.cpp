#include "Camera.h"

Camera::Camera() {
	screenWidth = 1;
	screenHeight = 1;
	position = glm::vec3(0.f);
	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);
	matrix = glm::mat4(1.0f);
}

Camera::Camera(float screenWidth, float screenHeight) {
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	double screen = (screenWidth / screenHeight);
	
	position = { 0.f, 0.f, -2.5f };
	view = glm::lookAt(position, position + glm::vec3(0., 0., 1.), glm::vec3(0.f, 1.0f, 0.f));
	projection = glm::ortho(-screen, screen, -1., 1., 0.01, 100.);
	//projection = glm::perspective(glm::radians(45.), screen, 0.1, 100.);
	matrix = projection * view;
}

Camera::~Camera() {

}

void Camera::Uniform(GLint loc) {
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Camera::Uniform(Shader& shader, std::string name) {
	shader.Use();
	glUniformMatrix4fv(shader.getUniform(name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Camera::update() {
	double screen = (screenWidth / screenHeight);

	view = glm::lookAt(position, position + glm::vec3(0., 0., 1.), glm::vec3(0.f, 1.0f, 0.f));
	projection = glm::ortho(-screen, screen, -1., 1., 0.01, 100.);
	//projection = glm::perspective(glm::radians(45.), screen, 0.1, 100.);
	matrix = projection * view;
}