#include"Model.h"

const unsigned int width = 800;
const unsigned int height = 800;


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Xay dung mo hinh", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Khởi tạo Window thất bại\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);

	Shader shader("default.vert", "default.frag");
	// xử lý các đối tượng có ánh sáng
	glm::vec4 mauSang = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 vtSang = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 DenSang = glm::mat4(1.0f);
	DenSang = glm::translate(DenSang, vtSang);

	shader.KichHoat();
	glUniform4f(glGetUniformLocation(shader.ID, "mauDen"), mauSang.x, mauSang.y, mauSang.z, mauSang.w);
	glUniform3f(glGetUniformLocation(shader.ID, "vtDen"), vtSang.x, vtSang.y, vtSang.z);
	glEnable(GL_DEPTH_TEST);

	GocNhin gocNhin(width, height, glm::vec3(0.0f, 0.1f, 2.0f));
	// chạy 1 mô hình 3D
	MoHinh moHinh("models/map/scene.gltf");

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.83f, 0.42f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		gocNhin.Inputs(window);
		gocNhin.CapNhat(45.0f, 0.1f, 100.0f);
		// vẽ 1 mô hình
		moHinh.Ve(shader, gocNhin);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	shader.Xoa();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}