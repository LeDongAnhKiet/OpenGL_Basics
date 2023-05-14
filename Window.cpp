#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main() 
{
	// khởi tạo glfw
	glfwInit();

	// setup version glfw đang dùng (opengl 3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// setup core profile đang dùng --> sử dụng hàm mới nhất
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// tạo glfw window cỡ 800x800, tên là Window
	GLFWwindow* window = glfwCreateWindow(800, 800, "Window", NULL, NULL);
	// kiểm tra nếu ko tạo đc
	if (window == NULL)
	{
		std::cout << "Failed!\n";
		glfwTerminate();
		return -1;
	}
	// tạo context cho window
	glfwMakeContextCurrent(window);
	// chạy GLAD = OpenGL
	gladLoadGL();

	// tạo viewport cho window từ x = y = 0 đến x = y = 800
	glViewport(0, 0, 800, 800);
	// chọn màu cho background
	glClearColor(1.2f, 0.75f, 0.35f, 1.2f);
	// xóa back buffer trước và đưa màu đã chọn vào đó
	glClear(GL_COLOR_BUFFER_BIT);
	// chuyển back buffer lên front buffer
	glfwSwapBuffers(window);

	// chạy window = vòng lặp
	while (!glfwWindowShouldClose(window))
		glfwPollEvents();

	// hủy window trước khi đóng chương trình
	glfwDestroyWindow(window);
	// hủy GLFW trước khi đóng chương trình
	glfwTerminate();
	return 0;
}