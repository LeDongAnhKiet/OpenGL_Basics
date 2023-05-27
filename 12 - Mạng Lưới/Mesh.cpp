#include "Mesh.h"

Luoi::Luoi(std::vector <ToaDo>& toado, std::vector <GLuint>& thutu, std::vector <HinhAnh>& anh)
{
	toaDo = toado;
	thuTu = thutu;
	hinhAnh = anh;

	vao.Bind();
	VBO vbo(toado);
	EBO ebo(thutu);

	vao.LinkAttr(vbo, 0, 3, GL_FLOAT, sizeof(ToaDo), (void*) 0);
	vao.LinkAttr(vbo, 1, 3, GL_FLOAT, sizeof(ToaDo), (void*)(3 * sizeof(float)));
	vao.LinkAttr(vbo, 2, 3, GL_FLOAT, sizeof(ToaDo), (void*)(6 * sizeof(float)));
	vao.LinkAttr(vbo, 3, 2, GL_FLOAT, sizeof(ToaDo), (void*)(9 * sizeof(float)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}

void Luoi::Ve(Shader& shader, GocNhin& gocnhin)
{
	shader.KichHoat();
	vao.Bind();
	unsigned int nPt, nPc = nPt = 0;

	for (unsigned int i = 0; i < hinhAnh.size(); i++)
	{
		std::string n;
		std::string type = hinhAnh[i].type;
		if (type == "phanTan") n = std::to_string(nPt++);
		else if (type == "phanChieu") n = std::to_string(nPc++);
		hinhAnh[i].texUnit(shader, (type + n).c_str(), i);
		hinhAnh[i].Bind();
	}
	glUniform3f(glGetUniformLocation(shader.ID, "vtCam"), gocnhin.ViTri.x, gocnhin.ViTri.y, gocnhin.ViTri.z);
	gocnhin.Xuat(shader, "camMat");
	glDrawElements(GL_TRIANGLES, thuTu.size(), GL_UNSIGNED_INT, 0);
}