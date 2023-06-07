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
// mẫu hình
GLuint mau = 12;
// đường cong Gamma
float γάμμα = 2.2f;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_SAMPLES, mau); <-- Ko hiệu quả với khung ảnh
	// ko dùng framebuffer thì dùng code trên
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(doRong, doCao, "Dieu chinh do nhay sac thai mau sac", NULL, NULL);
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
	glUniform1i(glGetUniformLocation(khung.ID, "gamma"), γάμμα);

	// cho phép điều chỉnh độ sâu
	glEnable(GL_DEPTH_TEST);
	// cho phép lật mặt hình ảnh
	glEnable(GL_CULL_FACE);
	// giữ mặt trước
	glCullFace(GL_FRONT);
	// lật ngược kim đồng hồ (counter clock-wise)
	glFrontFace(GL_CCW);
	// cho phép khử răng cưa
	glEnable(GL_MULTISAMPLE);
	// cho phép điều chỉnh sắc thái Gamma
	glEnable(GL_FRAMEBUFFER_SRGB);

	GocNhin gocNhin(doRong, doCao, glm::vec3(-0.5f, 0.8f, 1.0f));
	MoHinh banDo("models/map/scene.gltf");
	VAO vao = VAO();
	VBO vbo = VBO(dinh, sizeof(dinh));

	vao.Bind();
	vao.LinkAttr(vbo, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*)0);
	vao.LinkAttr(vbo, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	// hậu xử lý ảnh khử răng cưa
	FBO fbo1 = FBO();
	RBO rbo = RBO(doRong, doCao, mau);
	HinhAnh hinhAnh = HinhAnh(doRong, doCao, mau);
	fbo1.KtLoi();

	// hậu xử lý khung ảnh thường
	FBO fbo2 = FBO();
	HinhAnh khungAnh(doRong, doCao);
	fbo2.KtLoi();
	vao.Unbind();
	vbo.Unbind();
	fbo1.Unbind();
	rbo.Unbind();
	fbo2.Unbind();

	while (!glfwWindowShouldClose(window))
	{
		double tdt = 0.0, tdht = 0.0, ktg;
		GLuint dem = 0;
		tdht = glfwGetTime();
		ktg = tdht - tdt; dem++;
		if (ktg >= 1.0 / 30.0)
		{
			std::string fps = std::to_string((1.0 / ktg) * dem),
				ms = std::to_string((ktg / dem) * 1000),
				tieuDe = "Hieu chinh Gamma - " + fps + " FPS / " + ms + " ms";
			glfwSetWindowTitle(window, tieuDe.c_str());
			tdt = tdht; dem = 0;
		}
		fbo1.Bind();
		glClearColor(pow(0.83f, γάμμα), pow(0.42f, γάμμα), pow(0.1f, γάμμα), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);

		gocNhin.Inputs(window);
		gocNhin.CapNhat(45.0f, 0.1f, 100.0f);
		banDo.Ve(chuongTrinh, gocNhin);
		fbo2.Bind(fbo1, doRong, doCao);
		fbo1.Unbind();
		khung.KichHoat();

		vao.Bind();
		glDisable(GL_DEPTH_TEST);
		khungAnh.Bind();
		hinhAnh.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	chuongTrinh.Xoa();
	khung.Xoa();
	hinhAnh.Xoa();
	khungAnh.Xoa();

	vao.Xoa();
	vbo.Xoa();
	rbo.Xoa();
	fbo1.Xoa();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
