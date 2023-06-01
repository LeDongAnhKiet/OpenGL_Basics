#include "Model.h"

const unsigned int doRong = 800, doCao = 800, nWins = 50;
float kcNhin[nWins];

int soSanh(const void* a, const void* b)
{
	double kc = kcNhin[*(int*)b] - kcNhin[*(int*)a];
	return (0 < kc) - (kc < 0);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(doRong, doCao, "", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Khởi tạo Window thất bại\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, doRong, doCao);

	Shader shaderChuongTrinh("def.vert", "def.frag");
	Shader shaderBaiCo("baiCo.vert", "baiCo.frag");
	Shader shaderWindows("wins.vert", "wins.frag");
	glm::vec4 mauSang = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 vtSang = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 DenSang = glm::mat4(1.0f);
	DenSang = glm::translate(DenSang, vtSang);

	shaderChuongTrinh.KichHoat();
	glUniform4f(glGetUniformLocation(shaderChuongTrinh.ID, "mauDen"), mauSang.x, mauSang.y, mauSang.z, mauSang.w);
	glUniform3f(glGetUniformLocation(shaderChuongTrinh.ID, "vtDen"), vtSang.x, vtSang.y, vtSang.z);
	shaderBaiCo.KichHoat();
	glUniform4f(glGetUniformLocation(shaderBaiCo.ID, "mauDen"), mauSang.x, mauSang.y, mauSang.z, mauSang.w);
	glUniform3f(glGetUniformLocation(shaderBaiCo.ID, "vtDen"), vtSang.x, vtSang.y, vtSang.z);
	shaderWindows.KichHoat();
	glUniform4f(glGetUniformLocation(shaderWindows.ID, "mauDen"), mauSang.x, mauSang.y, mauSang.z, mauSang.w);
	glUniform3f(glGetUniformLocation(shaderWindows.ID, "vtDen"), vtSang.x, vtSang.y, vtSang.z);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);

	GocNhin gocNhin(doRong, doCao, glm::vec3(0.0f, 0.1f, 2.0f));
	MoHinh matDat("models/ground/scene.gltf");
	MoHinh baiCo("models/grass/scene.gltf");
	MoHinh windows("models/windows/scene.gltf");
	
	double tdt = 0.0, tdht = 0.0, ktg;
	glm::vec3 viTriWins[nWins];
	float xoayWins[nWins];
	unsigned int thuTuWins[nWins], dem = 0;

	for (unsigned int i = 0; i < nWins; i++)
	{
		viTriWins[i] = glm::vec3 (-25.0f + static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / (50.0f))),
			1.0f + static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / (3.0f))),
			-25.0f + static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / (50.0f))));
		xoayWins[i] = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / 1.0f));
		thuTuWins[i] = i;
	}

	while (!glfwWindowShouldClose(window))
	{
		tdht = glfwGetTime();
		ktg = tdht - tdt; dem++;
		if (ktg >= 1.0 / 30.0)
		{
			std::string fps = std::to_string((1.0 / ktg) * dem),
				ms = std::to_string((ktg / dem) * 1000),
				tieuDe = "Tron hinh anh trong suot - " + fps + " FPS / " + ms + " ms";
			glfwSetWindowTitle(window, tieuDe.c_str());
			tdt = tdht; dem = 0;
		}

		glClearColor(0.83f, 0.42f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		gocNhin.Inputs(window);
		gocNhin.CapNhat(45.0f, 0.1f, 100.0f);
		
		matDat.Ve(shaderChuongTrinh, gocNhin);
		glDisable(GL_CULL_FACE);
		baiCo.Ve(shaderBaiCo, gocNhin);
		glEnable(GL_BLEND);
		for (unsigned int i = 0; i < nWins; i++)
		{
			windows.Ve(shaderWindows, gocNhin, viTriWins[thuTuWins[i]], glm::quat(1.0f, 0.0f, xoayWins[thuTuWins[i]], 0.0f));
			kcNhin[i] = glm::length(gocNhin.ViTri - viTriWins[i]);
		}
		
		qsort(thuTuWins, nWins, sizeof(unsigned int), soSanh);
		glDisable(GL_BLEND);
		glEnable(GL_CULL_FACE);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	shaderChuongTrinh.Xoa();
	shaderBaiCo.Xoa();
	shaderWindows.Xoa();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}