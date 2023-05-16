#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VertexBufferObject.h"

class VAO
{
public:
	// tham chiếu đối tượng Vertex Array
	GLuint ID;
	// khởi tạo Vertex Buffer Object
	VAO();

	// kết nối VBO với VAO = 1 layout
	void LinkVBO(VBO& vbo, GLuint layout);
	// nối với VAO
	void Bind();
	// ngắt nối với VAO
	void Unbind();
	// xóa VAO
	void Delete();
};
#endif