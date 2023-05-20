#pragma once
#include <GL/glew.h>
#include <cmath>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

class Sprite
{
private:
	GLuint vboID;//, vboInsID;
	GLuint eboID;
	GLuint vaoID;
public:
	//std::vector<glm::mat4> instances;
	Sprite();
	~Sprite();
	//void updateInstances();
	void init();
	void Bind();
	void draw();
	void Unbind();
};

