#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO
{
public:
	// tham chiếu đối tượng Elements Buffer
	GLuint ID;
	// khởi tạo Elements Buffer Object và kết nối với các thứ tự điểm
	EBO(GLuint* indices, GLsizeiptr size);

	// nối với EBO
	void Bind();
	// ngắt nối với EBO
	void Unbind();
	// xóa EBO
	void Delete();
};

#endif