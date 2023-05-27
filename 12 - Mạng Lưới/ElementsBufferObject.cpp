#include "ElementsBufferObject.h"

EBO::EBO(std::vector<GLuint> thutu)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, thutu.size() * sizeof(GLuint), thutu.data(), GL_STATIC_DRAW);
}

void EBO::Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); }

void EBO::Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

void EBO::Xoa() { glDeleteBuffers(1, &ID); }