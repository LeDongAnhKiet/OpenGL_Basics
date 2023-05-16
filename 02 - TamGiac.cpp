#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// mã nguồn vertex shader 
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//mã nguồn fragment shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.82f, 0.37f, 0.05f, 1.08f);\n"
"}\n\0";

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(800, 800, "Tam giac", NULL, NULL);
	if (window == NULL)
		glfwTerminate();

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	// tạo vertex shader và gán tham chiếu
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// gán vertex shader source code vào vertex shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// biên dịch vertex shader thành ngôn ngữ máy
	glCompileShader(vertexShader);
	// tạo fragment shader và gán tham chiếu
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// gán fragment shader source code vào fragment shader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// biên dịch fragment shader thành ngôn ngữ máy
	glCompileShader(fragmentShader);
	// tạo shader program và gán tham chiếu
	GLuint shaderProgram = glCreateProgram();
	// gán fragment và vertex shader vào shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//liên kết các shader vào program
	glLinkProgram(shaderProgram);
	//Xóa các shader object
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//tọa độ các điểm
	GLfloat vertices[] =
	{
		// điểm trái dưới
		-0.5f, -0.5f * float(sqrt(5)) / 5, 0.0f,
		// điểm phải dưới
		0.5f, -0.5f * float(sqrt(5)) / 5, 0.0f,
		// điểm trên đầu
		0.0f, 0.5f * float(sqrt(5)) * 3 / 5, 0.0f
	};

	// tạo tham chiếu Vertex Array Object và Vertex Buffer Object
	GLuint VAO, VBO;
	// khởi tạo VAO, VBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// kết nối VAO với current Vertex Array Object
	glBindVertexArray(VAO);
	// kết nối VBO với GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// gán các vertices vào VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// cấu hình vertex attribute để OpenGL có thể đọc đc VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// kích hoạt vertex attribute để OpenGL sử dụng
	glEnableVertexAttribArray(0);
	// kết nối cả VBO, VAO thành 0 để ko gây lỗi nào khác
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glClearColor(1.2f, 0.75f, 0.35f, 1.2f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.15f, 0.02f, 0.18f, 1.5f);
		glClear(GL_COLOR_BUFFER_BIT);
		// gọi OpenGL sử dụng shader program
		glUseProgram(shaderProgram);
		// nối VAO lại OpenGL dùng
		glBindVertexArray(VAO);
		// vẽ hình tam giác = cách dùng GL_TRIANGLES
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		//xử lý sự kiện GLFW
		glfwPollEvents();
	}

	// xóa các đối tượng đã tạo
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
