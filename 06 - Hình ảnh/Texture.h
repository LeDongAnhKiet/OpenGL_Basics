#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H
#include <glad/glad.h>
#include <stb/img.h>
#include "Shader.h"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	Texture(const char* img, GLenum txType, GLenum slot, GLenum fm, GLenum pxType);

	// gán đơn vị ảnh vào hình ảnh
	void txUnit(Shader shade, const char* uni, GLuint unit);
	// nối ảnh
	void Bind();
	// ngắt nối ảnh
	void Unbind();
	// xóa ảnh
	void Delete();
};

#endif