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
// các tọa độ điểm
GLfloat diem[] =
{ //		Vị trí		/		Màu sắc		  /		Kết cấu		/		Thường		//
	-1.0f, 0.0f,  1.0f,     0.0f, 0.0f, 0.0f, 	 0.0f, 0.0f,      0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,     0.0f, 0.0f, 0.0f,	 0.0f, 1.0f,      0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, -1.0f,     0.0f, 0.0f, 0.0f,	 1.0f, 1.0f,      0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,     0.0f, 0.0f, 0.0f,	 1.0f, 0.0f,      0.0f, 1.0f, 0.0f,
};
// các thứ tự điểm
GLuint thutu[] =
{
	 0,  1,  2,
	 0,  2,  3
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

	Shader denSang("den.vert", "den.frag");
	VAO denVAO;
	denVAO.Bind();
	VBO denVBO(diemSang, sizeof(diemSang));
	EBO denEBO(thutuSang, sizeof(thutuSang));
	denVAO.LinkAttr(denVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

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

	// tạo kết cấu sàn và ánh sáng phản chiếu lên sàn
	KetCau san("pop_cat.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
	san.texUnit(chuongTrinh, "tex0", 0);
	KetCau phanChieu("bright.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
	phanChieu.texUnit(chuongTrinh, "tex1", 1);
	glEnable(GL_DEPTH_TEST);
	GocNhin GocNhin(doRong, doCao, glm::vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.15f, 0.02f, 0.18f, 1.5f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GocNhin.Inputs(window);
		GocNhin.CapNhat(40.0f, 0.1f, 200.0f);
		chuongTrinh.KichHoat();

		glUniform3f(glGetUniformLocation(chuongTrinh.ID, "vtCam"), GocNhin.ViTri.x, GocNhin.ViTri.y, GocNhin.ViTri.z);
		GocNhin.Xuat(chuongTrinh, "camMat");
		// nối kết cấu lại để chạy
		san.Bind();
		phanChieu.Bind();
		vao.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(thutu) / sizeof(int), GL_UNSIGNED_INT, 0);
		denSang.KichHoat();
		GocNhin.Xuat(denSang, "camMat");
		denVAO.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(thutuSang) / sizeof(int), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	vao.Xoa();
	vbo.Xoa();
	ebo.Xoa();
	san.Xoa();
	chuongTrinh.Xoa();

	denVAO.Xoa();
	denVBO.Xoa();
	denEBO.Xoa();
	denSang.Xoa();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}