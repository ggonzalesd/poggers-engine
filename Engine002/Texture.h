#pragma once
#include <GL/glew.h>
#include "Shader.h"

class Texture
{
private:
	static GLuint slotCount;
public:
	GLuint ID = 0;
	GLuint slot = 0;
	unsigned long width=0, height=0;

	Texture();
	Texture(const char* image, bool filter = false, GLint formatColor=GL_RGBA);

	void Uniform(GLuint position);
	void Uniform(Shader& shader, std::string name);
	void Bind();
	static void Unbind();
	void Delete();
};

