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
	HinhAnh(const char* img, const char* txType, GLuint slot);
	HinhAnh(int rong, int cao);
	HinhAnh(const char* img[]);

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Bind3D();
	void Unbind3D();
	void Xoa();
};
#endif