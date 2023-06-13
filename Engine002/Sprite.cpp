#include "Sprite.h"

Sprite::Sprite() {
	vboID = 0;
	eboID = 0;
	vaoID = 0;
}
Sprite::~Sprite() {
}

void Sprite::init() {
	if (vaoID == 0)
		glGenVertexArrays(1, &vaoID);
	if (vboID == 0)
		glGenBuffers(1, &vboID);
	if (eboID == 0)
		glGenBuffers(1, &eboID);

	float x = -0.5;
	float y = -0.5;

	float xw = x + 1.0f;
	float yh = y + 1.0f;

	float vertexData[] = {
	// |--Position--|  |----Color----|  |---UV---|  
		x,  y,  0.0,    1.0, 1.0, 1.0,   1.0, 1.0,
		xw, y,  0.0,    1.0, 1.0, 1.0,   0.0, 1.0,
		x,  yh, 0.0,    1.0, 1.0, 1.0,   1.0, 0.0,
		xw, yh, 0.0,    1.1, 1.0, 1.0,   0.0, 0.0,
	};

	GLuint indices[] = {
		0, 2, 1,
		1, 2, 3
	};

	glBindVertexArray(vaoID);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(sizeof(GLfloat) * 3));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(sizeof(GLfloat) * 6));
	for (GLuint i = 0; i < 3; i++)
		glEnableVertexAttribArray(i);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Sprite::Bind() {
	glBindVertexArray(vaoID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
}

void Sprite::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Sprite::draw() {
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}