#include "Mesh.h"
using namespace std;

Luoi::Luoi(vector <ToaDo>& toado, vector <GLuint>& thutu, vector <HinhAnh>& hinhanh)
{
	toaDo = toado, thuTu = thutu, hinhAnh = hinhanh;
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


void Luoi::Ve(Shader& shader, GocNhin& gocNhin, glm::mat4 matran,
	glm::vec3 dichchuyen, glm::quat xoay, glm::vec3 kichthuoc)
{
	// nối shader lại để nhận uniform
	shader.KichHoat();
	vao.Bind();
	// đếm số ảnh là phân tán hoặc phản chiếu
	GLuint nPt = 0, nPc = 0;

	for (GLuint i = 0; i < hinhAnh.size(); i++)
	{
		string n;
		string type = hinhAnh[i].type;
		if (type == "diffuse") n = to_string(nPt++);
		else if (type == "specular") n = to_string(nPc++);
		hinhAnh[i].texUnit(shader, (type + n).c_str(), i);
		hinhAnh[i].Bind();
	}
	// tạo góc nhìn
	glUniform3f(glGetUniformLocation(shader.ID, "vtCam"), gocNhin.ViTri.x, gocNhin.ViTri.y, gocNhin.ViTri.z);
	gocNhin.Xuat(shader, "camMat");

	// khởi tạo các ma trận
	glm::mat4 dc, x, kt = dc = x = glm::mat4(1.0f);
	// biến đổi các ma trận đó
	dc = glm::translate(dc, dichchuyen);
	x = glm::mat4_cast(xoay);
	kt = glm::scale(kt, kichthuoc);

	// đưa chúng vào vertex shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "dichchuyen"), 1, GL_FALSE, glm::value_ptr(dc));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "xoay"), 1, GL_FALSE, glm::value_ptr(x));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "kichthuoc"), 1, GL_FALSE, glm::value_ptr(kt));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "mohinh"), 1, GL_FALSE, glm::value_ptr(matran));
	// vẽ ra 1 lưới từ đó
	glDrawElements(GL_TRIANGLES, thuTu.size(), GL_UNSIGNED_INT, 0);
}