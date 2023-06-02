#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

// cấu trúc chuẩn các tọa độ điểm dùng trong mạng lưới
struct ToaDo
{
	glm::vec3 ViTri, Thuong, MauSac;
	glm::vec2 texUV;
};

class VBO
{
public:
	GLuint ID;
	VBO(std::vector<ToaDo>& toado);
	VBO(GLfloat* diem, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Xoa();
};

#endif