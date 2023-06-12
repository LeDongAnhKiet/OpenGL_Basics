#include "Model.h"

const GLuint doRong = 800, doCao = 800;
GLfloat dinh[] =
{
	 1.0f, -1.0f,	1.0f, 0.0f,
	-1.0f, -1.0f,	0.0f, 0.0f,
	-1.0f,  1.0f,	0.0f, 1.0f,

	 1.0f,  1.0f,	1.0f, 1.0f,
	 1.0f, -1.0f,	1.0f, 0.0f,
	-1.0f,  1.0f,	0.0f, 1.0f
};
GLuint mau = 8;
float gamma = 2.2f;
std::vector<ToaDo> diem =
{
	ToaDo{ glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
	ToaDo{ glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f) },
	ToaDo{ glm::vec3(1.0f , 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f) },
	ToaDo{ glm::vec3(1.0f , 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) }
};
std::vector<GLuint> chiSo =
{
	0, 1, 2,
	0, 2, 3
};

void FPS(GLFWwindow* win)
{
	double tdt = 0.0, tdht = 0.0, ktg;
	GLuint dem = 0;
	tdht = glfwGetTime();
	ktg = tdht - tdt; dem++;
	if (ktg >= 1.0 / 30.0)
	{
		std::string fps = std::to_string((1.0 / ktg) * dem),
			ms = std::to_string((ktg / dem) * 1000),
			tieuDe = "Chi tiet hoa be mat - " + fps + " FPS / " + ms + " ms";
		glfwSetWindowTitle(win, tieuDe.c_str());
		tdt = tdht; dem = 0;
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(doRong, doCao, "Normal Maps", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Khởi tạo Window thất bại\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, doRong, doCao);

	Shader chuongTrinh("def.vert", "def.frag", "def.geo");
	Shader shaderKhung("khung.vert", "khung.frag");
	glm::vec4 mauSang = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 vtSang = glm::vec3(0.5f, 10.0f, 0.5f);

	chuongTrinh.KichHoat();
	glUniform4f(glGetUniformLocation(chuongTrinh.ID, "mauDen"), mauSang.x, mauSang.y, mauSang.z, mauSang.w);
	glUniform3f(glGetUniformLocation(chuongTrinh.ID, "vtDen"), vtSang.x, vtSang.y, vtSang.z);
	shaderKhung.KichHoat();
	glUniform1i(glGetUniformLocation(shaderKhung.ID, "hinh"), 0);
	glUniform1i(glGetUniformLocation(shaderKhung.ID, "gamma"), gamma);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_FRAMEBUFFER_SRGB);

	GocNhin gocNhin(doRong, doCao, glm::vec3(0.0f, 0.2f, 1.7f));
	VAO vao = VAO();
	VBO vbo = VBO(dinh, sizeof(dinh));

	vao.Bind();
	vao.LinkAttr(vbo, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*)0);
	vao.LinkAttr(vbo, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	FBO fbo = FBO();
	RBO rbo = RBO(doRong, doCao, mau);
	HinhAnh mauAnh(doRong, doCao, mau, GL_TEXTURE_2D_MULTISAMPLE);
	fbo.KtLoi();

	FBO khungFbo = FBO();
	HinhAnh khungAnh(doRong, doCao);
	khungFbo.KtLoi();
	std::vector<HinhAnh> hinhAnh = 
	{
		HinhAnh("pop_cat.png", "phanTan", 0),
		HinhAnh("bright.png", "phanChieu", 1)
	};
	Luoi luoi(diem, chiSo, hinhAnh);
	HinhAnh chuanAnh("normal.png", "chuan", 2);

	vao.Unbind();
	vbo.Unbind();
	fbo.Unbind();
	rbo.Unbind();
	khungFbo.Unbind();

	while (!glfwWindowShouldClose(window))
	{
		FPS(window);
		fbo.Bind();
		glClearColor(pow(0.83f, gamma), pow(0.42f, gamma), pow(0.1f, gamma), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDisable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		gocNhin.Inputs(window);
		gocNhin.CapNhat(45.0f, 0.1f, 100.0f);
		chuongTrinh.KichHoat();
		chuanAnh.Bind();
		glUniform1i(glGetUniformLocation(chuongTrinh.ID, "chuan"), 1);

		luoi.Ve(chuongTrinh, gocNhin);
		khungFbo.Bind(fbo, doRong, doCao);
		fbo.Unbind();
		shaderKhung.KichHoat();

		vao.Bind();
		glDisable(GL_DEPTH_TEST);
		khungAnh.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	chuongTrinh.Xoa();
	shaderKhung.Xoa();
	mauAnh.Xoa();
	khungAnh.Xoa();
	hinhAnh[0].Xoa();
	chuanAnh.Xoa();

	vao.Xoa();
	vbo.Xoa();
	rbo.Xoa();
	fbo.Xoa();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}