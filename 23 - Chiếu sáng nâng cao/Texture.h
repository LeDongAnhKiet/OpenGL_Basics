#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <stb/img.h>
#include "Shader.h"
#include "FrameBufferObject.h"

class HinhAnh
{
public:
	GLuint ID, unit;
	const char* type;
	GLenum loai;
	HinhAnh(const char* img, const char* txType, GLuint slot);
	HinhAnh(int rong, int cao);
	HinhAnh(const char* img[]);
	HinhAnh(int rong, int cao, GLuint mau);
	HinhAnh(const char* image, const char* txType, GLuint slot, GLenum format, GLenum pixelType);

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Bind3D();
	void Unbind3D();
	void Xoa();
};

#endif