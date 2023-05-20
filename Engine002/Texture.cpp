#include "Texture.h"
#include "fileloader.h"
#include "picopng.h"
#include "Error.h"

GLuint Texture::slotCount = 0;

Texture::Texture() { }

Texture::Texture(const char* image, bool filter, GLint formatColor) {
	slot = slotCount++;
	std::vector<unsigned char>in;
	std::vector<unsigned char>out;

	readFileContent(image, in);
	int errorCode = decodePNG(out, width, height, &in[0], in.size());
	if (errorCode != 0)
		fatalError("decode PNG with error " + std::to_string(errorCode));

	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter ? GL_LINEAR : GL_NEAREST);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter ? GL_LINEAR : GL_NEAREST);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Uniform(GLuint position) {
	glUniform1i(position, slot);
}
void Texture::Uniform(Shader& shader, std::string name) {
	shader.Use();
	glUniform1i(shader.getUniform(name.c_str()), slot);
}

void Texture::Bind() {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ID);
}
void Texture::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::Delete() {
	glDeleteTextures(1, &ID);
}