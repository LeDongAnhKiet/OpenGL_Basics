#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <stb/img.h>
#include "Shader.h"

class HinhAnh
{
public:
	GLuint ID, unit;
	const char* type;
	HinhAnh(const char* image, const char* txType, GLuint slot, GLenum format, GLenum pixelType);

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Xoa();
};
#endif