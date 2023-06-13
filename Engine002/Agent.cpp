#include "Agent.h"

Agent::Agent(Texture* texture_, const glm::vec3& position_, const glm::vec3& color_) {
	texture = texture_;
	position = position_;
	color = color_;
}

Agent::~Agent() {

}

void Agent::Uniform(Shader& shader) {
	GLint uModel = shader.getUniform("uModel");
	GLint uTexture = shader.getUniform("uTexture");
	GLint uColor = shader.getUniform("uColor");
	Uniform(uModel, uTexture, uColor);
}

void Agent::Uniform(GLint uModel, GLint uTexture, GLint uColor) {
	if (texture)
		texture->Uniform(uTexture);
	glUniform3fv(uColor, 1, glm::value_ptr(this->color));
	glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(model));
}

void Agent::updateModel() {
	model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(scale));
	model = glm::rotate(model, angle, glm::vec3(0.f, 0.f, 1.0f));
}

void Agent::Draw(Sprite& sprite) {
	if (texture)
		texture->Bind();
	sprite.draw();
	if (texture)
		texture->Unbind();
}