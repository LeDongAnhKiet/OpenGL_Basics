#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>
#include <vector>

class EBO
{
public:
	GLuint ID;
	EBO(std::vector<GLuint> chiso);
	EBO(GLuint* chiso, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Xoa();
};

#endif