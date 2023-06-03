#include "VertexArrayObject.h"

VAO::VAO() 
{
	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);
}

void VAO::LinkAttr(VBO& VBO, GLuint layout, GLuint nComponent, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, nComponent, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VAO::Bind() { glBindVertexArray(ID); }

void VAO::Unbind() { glBindVertexArray(0); }

void VAO::Xoa() { glDeleteVertexArrays(1, &ID); }