#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string>
#include "ElementsBufferObject.h"
#include "VertexArrayObject.h"
#include "Perspective.h"
#include "Texture.h"

class Luoi
{
public:
	std::vector <ToaDo> toaDo;
	std::vector <GLuint> thuTu;
	std::vector <HinhAnh> hinhAnh;
	GLuint nhanBan;
	// chứa VAO công khai để dùng cho hàm Vẽ
	VAO vao;

	// khởi tạo lưới
	Luoi(std::vector <ToaDo>& toado, std::vector <GLuint>& thutu, std::vector <HinhAnh>& hinhanh,
		GLuint nhanban = 1, std::vector<glm::mat4> matran = {});
	// vẽ cái lưới
	void Ve(Shader& shader, GocNhin& gocNhin, glm::mat4 matran = glm::mat4(1.0f),
		glm::vec3 dichchuyen = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat xoay = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 kichthuoc = glm::vec3(1.0f, 1.0f, 1.0f));
};
#endif