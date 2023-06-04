#include "VertexBufferObject.h"

VBO::VBO(std::vector<ToaDo>& toado)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, toado.size() * sizeof(ToaDo), toado.data(), GL_STATIC_DRAW);
}

VBO::VBO(std::vector<glm::mat4>& matran)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, matran.size() * sizeof(glm::mat4), matran.data(), GL_STATIC_DRAW);
}

VBO::VBO(GLfloat* diem, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, diem, GL_STATIC_DRAW);
}
void VBO::Bind() { glBindBuffer(GL_ARRAY_BUFFER, ID); }

void VBO::Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void VBO::Xoa() { glDeleteBuffers(1, &ID); }