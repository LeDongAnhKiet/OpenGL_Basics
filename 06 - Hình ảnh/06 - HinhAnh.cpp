#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ElementsBufferObject.h"
#include "Shader.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include <stb/img.h>
#include "Texture.h"

// tọa độ các điểm
GLfloat vertices[] =
{
					// điểm trái dưới
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					// điểm trái trên
	-0.5f, 0.5f , 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
					// điểm phải trên
	0.5f , 0.5f , 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
					// điểm phải dưới
	0.5f , -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f
};
// thứ tự các điểm
GLuint indices[] =
{
	0, 2, 1,	 // tam giác trên
	0, 3, 2		// tam giác dưới
};

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Hinh anh", NULL, NULL);
	if (window == NULL) glfwTerminate();
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	Shader shader("default.vert", "default.frag");
	VAO vao;
	vao.Bind();
	VBO vbo(vertices, sizeof(vertices));
	EBO ebo(indices, sizeof(indices));

	vao.LinkAttr(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	vao.LinkAttr(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.LinkAttr(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	GLuint uni = glGetUniformLocation(shader.ID, "scale");
	// hình ảnh
	Texture kirby("kirby.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	kirby.txUnit(shader, "tex", 0);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.25f, 0.12f, 0.58f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.Activate(); 

		glUniform1f(uni, 0.5f);
		// nối hình lại để chạy đc hình
		kirby.Bind();
		vao.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	shader.Delete();
	kirby.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}