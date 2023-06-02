#ifndef FBO_CLASS_H
#define FBO_CLASS_H

#include <glad/glad.h>

class FBO
{
public:
	GLuint ID;
	FBO();

	void Bind();
	void Unbind();
	void Xoa();
	void KtLoi();
};

class RBO
{
public:
	GLuint ID;
	RBO(int rong, int cao);

	void Bind();
	void Unbind();
	void Xoa();
};

#endif