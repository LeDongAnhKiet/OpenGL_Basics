#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ElementsBufferObject.h"
#include "Shader.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

// tọa độ các điểm
GLfloat vertices[] =
{		
	-0.4f , -0.4f * float(sqrt(5))	  / 5, 0.0f, 0.8f, 0.3f , 0.02f,	// điểm trái dưới	
	0.4f  , -0.4f * float(sqrt(5))	  / 5, 0.0f, 0.8f, 0.3f , 0.02f,	// điểm phải dưới
	0.0f  , 0.4f * float(sqrt(5)) * 3 / 5, 0.0f, 1.0f, 0.6f , 0.32f,	// điểm trên cùng
	-0.4f / 2, 0.4f * float(sqrt(5))  / 5, 0.0f, 0.9f, 0.45f, 0.17f,	// trung điểm trái
	0.4f  / 2, 0.4f * float(sqrt(5))  / 5, 0.0f, 0.9f, 0.45f, 0.17f,	// trung điểm phải
	0.0f  , -0.4f * float(sqrt(5))	  / 5, 0.0f, 0.8f, 0.3f , 0.02f		// trung điểm dưới
};
// thứ tự các điểm
GLuint indices[] =
{
	0, 3, 5,	  // tam giác trái 
	3, 2, 4,	 // tam giác phải
	5, 4, 1		// tam giác trên
};

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "To bong cho tam giac", NULL, NULL);
	if (window == NULL) glfwTerminate();
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	Shader shader("default.vert", "default.frag");
	VAO vao;
	vao.Bind();
	VBO vbo(vertices, sizeof(vertices));
	EBO ebo(indices, sizeof(indices));
	// kết nối thuộc tính VBO (tọa độ, thứ tự điểm) với VAO
	vao.LinkAttr(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	vao.LinkAttr(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
	// lấy uniform tên là "scale"
	GLuint uni = glGetUniformLocation(shader.ID, "scale");

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.15f, 0.02f, 0.18f, 1.5f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.Activate();
		// gán giá trị vào uniform SAU khi đã kích hoạt Shader
		glUniform1f(uni, 0.5f);
		vao.Bind();
		// vẽ kiểu hình, số điểm, kiểu dữ liệu, chỉ số đầu 
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	shader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
