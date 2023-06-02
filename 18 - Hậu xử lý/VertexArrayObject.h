#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VertexBufferObject.h"

class VAO
{
public:
	GLuint ID;
	VAO();

	void LinkAttr(VBO& VBO, GLuint layout, GLuint nComponent, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
	void Xoa();
};

#endif