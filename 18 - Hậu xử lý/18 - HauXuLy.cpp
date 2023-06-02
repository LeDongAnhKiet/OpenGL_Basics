#include "Model.h"

const GLuint doRong = 800, doCao = 800;
// đỉnh các điểm
GLfloat dinh[] =
{
	// tọa độ điểm	/ tọa độ hình
	 1.0f, -1.0f,	1.0f, 0.0f,
	-1.0f, -1.0f,	0.0f, 0.0f,
	-1.0f,  1.0f,	0.0f, 1.0f,

	 1.0f,  1.0f,	1.0f, 1.0f,
	 1.0f, -1.0f,	1.0f, 0.0f,
	-1.0f,  1.0f,	0.0f, 1.0f
};

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(doRong, doCao, "Framebuffer", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Khởi tạo Window thất bại\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, doRong, doCao);

	Shader chuongTrinh("def.vert", "def.frag");
	Shader khung("khung.vert", "khung.frag");
	glm::vec4 mauSang = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 vtSang = glm::vec3(0.5f, 0.5f, 0.5f);

	chuongTrinh.KichHoat();
	glUniform4f(glGetUniformLocation(chuongTrinh.ID, "mauDen"), mauSang.x, mauSang.y, mauSang.z, mauSang.w);
	glUniform3f(glGetUniformLocation(chuongTrinh.ID, "vtDen"), vtSang.x, vtSang.y, vtSang.z);
	khung.KichHoat();
	glUniform1i(glGetUniformLocation(khung.ID, "hinh"), 0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	GocNhin gocNhin(doRong, doCao, glm::vec3(0.0f, 0.1f, 2.0f));
	MoHinh banDo("models/map/scene.gltf");
	VAO vao = VAO();
	VBO vbo = VBO(dinh, sizeof(dinh));
	vao.Bind();
	vao.LinkAttr(vbo, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*) 0);
	vao.LinkAttr(vbo, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	
	double tdt = 0.0, tdht = 0.0, ktg;
	GLuint dem = 0;
	FBO fbo = FBO();
	RBO rbo = RBO(doRong, doCao);
	HinhAnh khungAnh = HinhAnh(doRong, doCao);

	vao.Unbind();
	vbo.Unbind();
	fbo.Unbind();
	rbo.Unbind();

	while (!glfwWindowShouldClose(window))
	{
		tdht = glfwGetTime();
		ktg = tdht - tdt; dem++;
		if (ktg >= 1.0 / 30.0)
		{
			std::string fps = std::to_string((1.0 / ktg) * dem),
				ms = std::to_string((ktg / dem) * 1000),
				tieuDe = "Hau xu ly - " + fps + " FPS / " + ms + " ms";
			glfwSetWindowTitle(window, tieuDe.c_str());
			tdt = tdht; dem = 0;
		}
		fbo.Bind();
		glClearColor(0.83f, 0.42f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);

		gocNhin.Inputs(window);
		gocNhin.CapNhat(45.0f, 0.1f, 100.0f);
		banDo.Ve(chuongTrinh, gocNhin);
		fbo.Unbind();
		khung.KichHoat();
		
		vao.Bind();
		glDisable(GL_DEPTH_TEST);
		khungAnh.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	chuongTrinh.Xoa();
	khung.Xoa();
	khungAnh.Xoa();

	vao.Xoa();
	vbo.Xoa();
	rbo.Xoa();
	fbo.Xoa();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}