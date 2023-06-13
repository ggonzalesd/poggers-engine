#pragma once
#include <GL/glew.h>
#include <cmath>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

class Sprite
{
private:
	GLuint vboID;
	GLuint eboID;
	GLuint vaoID;
public:
	Sprite();
	~Sprite();
	void init();
	void Bind();
	void draw();
	void Unbind();
};

