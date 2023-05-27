#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string>
#include "VertexArrayObject.h"
#include "ElementsBufferObject.h"
#include "Texture.h"
#include "Perspective.h"

class Luoi
{
public:
	std::vector <ToaDo> toaDo;
	std::vector <GLuint> thuTu;
	std::vector <HinhAnh> hinhAnh;

	// chứa VAO công khai để dùng cho hàm Vẽ
	VAO vao;
	// khởi tạo lưới
	Luoi(std::vector <ToaDo>& toado, std::vector <GLuint>& thutu, std::vector <HinhAnh>& anh);
	// vẽ cái lưới
	void Ve(Shader& shader, GocNhin& gocnhin);
};

#endif