#pragma once
#include <GL/glew.h>
#include <cmath>

class Sprite
{
private:
	float x, y;
	int width, height;
	float vertexData;
	GLuint vboID;
	GLuint eboID;
public:
	Sprite();
	~Sprite();
	void init(float x, float y, int width, int height);
	void draw();

};

