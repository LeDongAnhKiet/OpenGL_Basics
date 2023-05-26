#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/img.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
		 
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "ElementsBufferObject.h"
#include "Shader.h"
#include "Texture.h"
#include "Perspective.h"

const unsigned int doRong = 800, doCao = 800;

GLfloat diem[] =
{ //     Tọa độ điểm     /        Màu sắc      /   Tọa độ kết cấu  /	Tọa độ thường	//
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, 
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // mặt đáy
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, 
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, 

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // mặt trái
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, 
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, 

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // mặt khuất
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, 
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, 

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // mặt phải
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, 
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, 

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // mặt chính diện
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, 
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  
};
GLuint thutu[] =
{
	 0,  1,  2,	// mặt đáy
	 0,  2,  3,    // hướng đáy
	 4,  6,  5,   // hướng trái
	 7,  9,  8,  // hướng khuất
	10, 12, 11, // hướng phải
	13, 15, 14 // hướng chính diện
};
// các tọa độ điểm sáng
GLfloat diemSang[] =
{
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};
// các thứ tự điểm sáng
GLuint thutuSang[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(doRong, doCao, "YoutubeOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Khởi tạo Window thất bại\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, doRong, doCao);

	Shader chuongTrinh("default.vert", "default.frag");
	VAO vao;
	vao.Bind();
	VBO vbo(diem, sizeof(diem));
	EBO ebo(thutu, sizeof(thutu));

	vao.LinkAttr(vbo, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	vao.LinkAttr(vbo, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.LinkAttr(vbo, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	vao.LinkAttr(vbo, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	// tạo Shader cho đèn chiếu sáng hình lập phương
	Shader denSang("den.vert", "den.frag");
	// tạo đối tượng Vertex Array và nối lại
	VAO denVAO;
	denVAO.Bind();
	// tạo đối tượng Vertex Buffer và nối với các tọa độ điểm
	VBO denVBO(diemSang, sizeof(diemSang));
	// tạo đối tượng Element Buffer và nối với các thứ tự điểm
	EBO denEBO(thutuSang, sizeof(thutuSang));
	// nối các thuộc tính VBO như các tọa độ, màu sắc với VAO
	denVAO.LinkAttr(denVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	// ngắt nối các đối tượng để tránh sửa đổi
	denVAO.Unbind();
	denVBO.Unbind();
	denEBO.Unbind();

	glm::vec4 mauSang = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 vtSang = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 mhDen = glm::mat4(1.0f);
	mhDen = glm::translate(mhDen, vtSang);

	glm::vec3 vtHinh = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 mHinh = glm::mat4(1.0f);
	mHinh = glm::translate(mHinh, vtHinh);

	denSang.KichHoat();
	glUniformMatrix4fv(glGetUniformLocation(denSang.ID, "mohinh"), 1, GL_FALSE, glm::value_ptr(mhDen));
	glUniform4f(glGetUniformLocation(denSang.ID, "mauDen"), mauSang.x, mauSang.y, mauSang.z, mauSang.w);
	chuongTrinh.KichHoat();
	glUniformMatrix4fv(glGetUniformLocation(chuongTrinh.ID, "mohinh"), 1, GL_FALSE, glm::value_ptr(mHinh));
	glUniform4f(glGetUniformLocation(chuongTrinh.ID, "mauDen"), mauSang.x, mauSang.y, mauSang.z, mauSang.w);
	glUniform3f(glGetUniformLocation(chuongTrinh.ID, "vtDen"), vtSang.x, vtSang.y, vtSang.z);

	Texture ketCau("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	ketCau.texUnit(chuongTrinh, "tex", 0);
	glEnable(GL_DEPTH_TEST);
	// tạo đối tượng Góc nhìn
	GocNhin GocNhin(doRong, doCao, glm::vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.15f, 0.02f, 0.18f, 1.5f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// xử lý phím nhập cho góc nhìn
		GocNhin.Inputs(window);
		// cập nhật ma trận cho Vertex shader
		GocNhin.CapNhat(40.0f, 0.1f, 200.0f);

		// cho OpenGL biết shader nào để sử dụng
		chuongTrinh.KichHoat();
		// xuất vị trí góc nhìn cho Fragment Shader để chiếu sáng
		glUniform3f(glGetUniformLocation(chuongTrinh.ID, "vtCam"), GocNhin.ViTri.x, GocNhin.ViTri.y, GocNhin.ViTri.z);
		// xuất camMat cho Vertex Shader của kết cấu
		GocNhin.Xuat(chuongTrinh, "camMat");
		// nối kết cấu lại để chạy
		ketCau.Bind();
		// nối VAO lại để OpenGL dùng
		vao.Bind();
		// vẽ = số điểm, kiểu dữ liệu và thứ tự điểm
		glDrawElements(GL_TRIANGLES, sizeof(thutu) / sizeof(int), GL_UNSIGNED_INT, 0);

		// cho OpenGL biết shader nào để sử dụng
		denSang.KichHoat();
		// xuất camMat cho Vertex shader của đèn sáng
		GocNhin.Xuat(denSang, "camMat");
		// nối VAO lại để OpenGL sử dụng
		denVAO.Bind();
		// vẽ = số điểm sáng, kiểu dữ liệu và thứ tự điểm sáng
		glDrawElements(GL_TRIANGLES, sizeof(thutuSang) / sizeof(int), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}



	vao.Xoa();
	vbo.Xoa();
	ebo.Xoa();
	ketCau.Xoa();
	chuongTrinh.Xoa();
	// xóa cả các đối tượng đèn chiếu sáng đã tạo
	denVAO.Xoa();
	denVBO.Xoa();
	denEBO.Xoa();
	denSang.Xoa();
	// xóa window trước khi kết thúc chương trình
	glfwDestroyWindow(window);
	// hủy GLFW trước khi kết thúc chương trình
	glfwTerminate();
	return 0;
}
