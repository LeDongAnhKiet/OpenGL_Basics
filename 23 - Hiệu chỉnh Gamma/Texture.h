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
	HinhAnh(const char* img, const char* txType, GLuint slot);
	HinhAnh(int rong, int cao);
	HinhAnh(const char* img[]);
	HinhAnh(int rong, int cao, GLuint mau);
	HinhAnh(const char* img, const char* txType, GLuint slot, GLenum fm, GLenum pxType);

	void texUnit(Shader& shader, const char* unif, GLuint unit);
	void Bind();
	void Unbind();
	void Bind3D();
	void Unbind3D();
	void Xoa();
};

#endif