#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>
#include "fileloader.h"

class Shader
{
public:
	GLuint ID;

	Shader();
	Shader(const std::string vertexFilename, const std::string fragmentFilename, const std::vector<std::string>& attribs = {});

	GLint getUniform(const GLchar* name);
	void BindAttribs(const std::vector<std::string>& attribs);

	void Use();
	void Delete();
};

