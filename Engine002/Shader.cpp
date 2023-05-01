#include "Shader.h"

GLuint createShader(GLenum type, const std::string name, const char** source) {
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, source, nullptr);
	glCompileShader(shader);

	GLint isCompiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar* errorLog = new GLchar[maxLength];
		glGetShaderInfoLog(shader, maxLength, &maxLength, errorLog);

		std::cerr << "[ERROR]: Shader no compiled" << std::endl;
		std::cerr << "[FILE: '" << name << "']" << std::endl;
		std::cerr << errorLog << std::endl;
		delete[] errorLog;
	}
	return shader;
}

void testLink(GLuint ID, const std::string vertexName, const std::string fragmentName) {
	GLint isLinked = 0;
	glGetProgramiv(ID, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar* errorLog = new GLchar[maxLength];
		glGetProgramInfoLog(ID, maxLength, &maxLength, errorLog);

		std::cerr << "[ERROR]: Program no linked" << std::endl;
		std::cerr << "[Vertex: '" << vertexName << "']" << std::endl;
		std::cerr << "[Fragment: '" << fragmentName << "']" << std::endl;
		std::cerr << errorLog << std::endl;
		delete[] errorLog;
	}
}

Shader::Shader()
{
	ID = 0;
}

Shader::Shader(const std::string vertexFilename, const std::string fragmentFilename, const std::vector<std::string>& attribs)
{
	const char* vertexShaderSource = getFileContent(vertexFilename);
	GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexFilename, &vertexShaderSource);

	const char* fragmentShaderSource = getFileContent(fragmentFilename);
	GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentFilename, &fragmentShaderSource);

	ID = glCreateProgram();
	BindAttribs(attribs);

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);

	testLink(ID, vertexFilename, fragmentFilename);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	delete[] vertexShaderSource;
	delete[] fragmentShaderSource;
}

void Shader::BindAttribs(const std::vector<std::string>& attribs)
{
	for (size_t i=0; i< attribs.size(); i++)
	{
		glBindAttribLocation(ID, i, attribs[i].c_str());
	}
}

GLint Shader::getUniform(const GLchar* name)
{
	return glGetUniformLocation(ID, name);
}

void Shader::Use()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}
