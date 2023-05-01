#include "Sprite.h"

Sprite::~Sprite() {
	if (vboID != 0)
		glDeleteBuffers(1, &vboID);
	if (eboID != 0)
		glDeleteBuffers(1, &eboID);
}

void Sprite::init(float x, float y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	if (vboID == 0)
		glGenBuffers(1, &vboID);
	if (eboID == 0)
		glGenBuffers(1, &eboID);

	float xw = x + width;
	float yh = y + height;

	float vertexData[] = {
	// |--Position--|  |----Color----|  |---UV---|  
		x,  y,  0.0,    1.0, 1.0, 0.0,   0.0, 0.0,
		xw, y,  0.0,    0.0, 1.0, 1.0,   0.0, 0.0,
		x,  yh, 0.0,    1.0, 0.0, 1.0,   0.0, 0.0,
		xw, yh, 0.0,    0.1, 1.0, 0.1,   0.0, 0.0,
	};

	GLuint indices[] = {
		0, 2, 1,
		1, 2, 3
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Sprite::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(sizeof(GLfloat) * 3));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(sizeof(GLfloat) * 6));
	for(GLuint i=0; i<3; i++)
		glEnableVertexAttribArray(i);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	for (GLuint i = 0; i < 3; i++)
		glDisableVertexAttribArray(i);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}