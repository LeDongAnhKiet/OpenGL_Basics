#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "ElementBufferObject.h"
#include "ShaderClass.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

//tọa độ các điểm
GLfloat vertices[] =
{
	// điểm trái dưới
	-0.5f, -0.5f * float(sqrt(5)) / 5, 0.0f,
	// điểm phải dưới
	0.5f, -0.5f * float(sqrt(5)) / 5, 0.0f,
	// điểm trên cùng
	0.0f, 0.5f * float(sqrt(5)) * 3 / 5, 0.0f,
	// trung điểm trái
	-0.5f / 2, 0.5f * float(sqrt(5)) / 5, 0.0f,
	// trung điểm phải
	0.5f / 2, 0.5f * float(sqrt(5)) / 5, 0.0f,
	// trung điểm dưới
	0.0f, -0.5f * float(sqrt(5)) / 5, 0.0f
};
//thứ tự các điểm
GLuint indices[] =
{
	0, 3, 5,	// tam giác trái 
	3, 2, 4,	// tam giác phải
	5, 4, 1		// tam giác trên
};

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "3 Tam giac thanh 1 tam giac lon", NULL, NULL);
	if (window == NULL)
		glfwTerminate();

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	// tạo đối tượng Shader = cách dùng default.vert và default.frag
	Shader shade("default.vert", "default.frag");
	// tạo Vertex Array Object và nối lại
	VAO vao;
	vao.Bind();
	// tạo Vertex Buffer Object và kết nối các tọa độ điểm
	VBO vbo(vertices, sizeof(vertices));
	// tạo Element Buffer Object và kết nối các thứ tự điểm
	EBO ebo(indices, sizeof(indices));
	// nối VBO lại VAO
	vao.LinkVbo(vbo, 0);
	//Ngắt kết nối các đối tượng để ko xảy ra lỗi ngoài ý muốn
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.15f, 0.02f, 0.18f, 1.5f);
		glClear(GL_COLOR_BUFFER_BIT);
		shade.Activate();
		vao.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	shade.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}