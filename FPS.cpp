#include "Model.h"

const unsigned int doRong = 800, doCao = 800;


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

	Shader chuongTrinh("default.vert", "default.frag");
	Shader duongVien("vien.vert", "vien.frag");
	glm::vec4 mauSang = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 vtSang = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 DenSang = glm::mat4(1.0f);
	DenSang = glm::translate(DenSang, vtSang);

	chuongTrinh.KichHoat();
	glUniform4f(glGetUniformLocation(chuongTrinh.ID, "mauDen"), mauSang.x, mauSang.y, mauSang.z, mauSang.w);
	glUniform3f(glGetUniformLocation(chuongTrinh.ID, "vtDen"), vtSang.x, vtSang.y, vtSang.z);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	// lật mặt sau thành mặt trước
	glEnable(GL_CULL_FACE);
	// giữ mặt trước
	glCullFace(GL_FRONT);
	// theo đúng chiều
	glFrontFace(GL_CW);

	GocNhin gocNhin(doRong, doCao, glm::vec3(0.0f, 0.1f, 2.0f));
	MoHinh banDo("models/map/scene.gltf");
	MoHinh tho("models/bunny/scene.gltf");
	// thời điểm trước, thời điểm hiện tại, khoảng thời gian giữa 2 thời điểm đó
	double tdt = 0.0, tdht = 0.0, ktg;
	// đếm số khung trên giây (FPS) trong khoảng thời gian đó
	unsigned int dem = 0;
	// tắt đồng bộ hóa (ko nên tắt)
	glfwSwapInterval(0);

	while (!glfwWindowShouldClose(window))
	{
		tdht = glfwGetTime();
		ktg = tdht - tdt; dem++;
		if (ktg >= 1.0 / 30.0)
		{
			// đặt tựa đề chương trình
			std::string fps = std::to_string((1.0 / ktg) * dem),
				ms = std::to_string((ktg / dem) * 1000),
				tieuDe = fps + " FPS / " + ms + " ms";
			glfwSetWindowTitle(window, tieuDe.c_str());
			tdt = tdht; dem = 0;
			// nếu tắt thì dùng
			gocNhin.Inputs(window);
		}

		glClearColor(0.83f, 0.42f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		gocNhin.CapNhat(45.0f, 0.1f, 100.0f);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		
		banDo.Ve(chuongTrinh, gocNhin);
		tho.Ve(chuongTrinh, gocNhin);
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);
		duongVien.KichHoat();
		glUniform1f(glGetUniformLocation(duongVien.ID, "vien"), 0.1f);
		
		banDo.Ve(duongVien, gocNhin);
		tho.Ve(duongVien, gocNhin);
		glStencilMask(0xFF);
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		glEnable(GL_DEPTH_TEST);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	chuongTrinh.Xoa();
	duongVien.Xoa();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}