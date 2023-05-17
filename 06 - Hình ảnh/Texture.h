#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H
#include <glad/glad.h>
#include <stb/img.h>
#include "shaderClass.h"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	Texture(const char* img, GLenum txType, GLenum slot, GLenum fm, GLenum pxType);

	// gán đơn vị ảnh vào hình ảnh
	void texUnit(Shader& shader, const char* uni, GLuint unit);
	// nối ảnh
	void Bind();
	// ngắt nối ảnh
	void Unbind();
	// xóa ảnh
	void Delete();
};

#endif
