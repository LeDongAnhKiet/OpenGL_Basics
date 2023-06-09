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
GLuint mau = 12;
float gamma = 2.2f;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(doRong, doCao, "Shadow Maps", NULL, NULL);
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
	Shader shaderKhung("khung.vert", "khung.frag");
	Shader shaderToi("toi.vert", "toi.frag");
	Shader shaderKhoi("khoi.vert", "khoi.frag", "khoi.geo");
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

	GocNhin gocNhin(doRong, doCao, glm::vec3(-0.5f, 0.8f, 1.0f));
	MoHinh banDo("models/map/scene.gltf");
	VAO vao = VAO();
	VBO vbo = VBO(dinh, sizeof(dinh));

	vao.Bind();
	vao.LinkAttr(vbo, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*)0);
	vao.LinkAttr(vbo, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	// hậu xử lý chương trình, hình ảnh
	FBO fbo = FBO();
	RBO rbo = RBO(doRong, doCao, mau);
	HinhAnh hinhAnh(doRong, doCao, mau, GL_TEXTURE_2D_MULTISAMPLE);
	fbo.KtLoi();

	// hậu xử lý khung hình
	FBO khungFbo = FBO();
	HinhAnh khungAnh(doRong, doCao);
	khungFbo.KtLoi();
	// hậu xử lý vùng tối
	GLuint bongToi = 2048;
	FBO toiFbo = FBO();
	HinhAnh vungToi(bongToi, bongToi, GL_DEPTH_COMPONENT);
	toiFbo.Bind(vungToi);

	vao.Unbind();
	vbo.Unbind();
	fbo.Unbind();
	rbo.Unbind();
	khungFbo.Unbind();

	// ma trận tạo hướng sáng
	float tamXa = 100.0f;
	glm::mat4 vuongGoc = glm::ortho(-35.0f, 35.0f, -35.0f, 35.0f, 0.1f, tamXa),
		huongSang = glm::lookAt(vtSang, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
		huongNhin = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, tamXa),
		chieuSang = vuongGoc * huongSang * huongNhin;
	shaderToi.KichHoat();
	glUniformMatrix4fv(glGetUniformLocation(shaderToi.ID, "denChieu"), 1, GL_FALSE, glm::value_ptr(chieuSang));

	// hậu xử lý điểm tối
	FBO diemFbo = FBO();
	HinhAnh khoiKhungAnh(bongToi, GL_TEXTURE_CUBE_MAP, GL_DEPTH_COMPONENT);
	// ma trận hướng chuyển tối
	glm::mat4 huongToi = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, tamXa),
		chuyenToi[] = 
	{
	huongToi * glm::lookAt(vtSang, vtSang + glm::vec3(1.0 ,  0.0,  0.0), glm::vec3(0.0, -1.0,  0.0)),
	huongToi * glm::lookAt(vtSang, vtSang + glm::vec3(-1.0,  0.0,  0.0), glm::vec3(0.0, -1.0,  0.0)),
	huongToi * glm::lookAt(vtSang, vtSang + glm::vec3(0.0 ,  1.0,  0.0), glm::vec3(0.0,  0.0,  1.0)),
	huongToi * glm::lookAt(vtSang, vtSang + glm::vec3(0.0 , -1.0,  0.0), glm::vec3(0.0,  0.0, -1.0)),
	huongToi * glm::lookAt(vtSang, vtSang + glm::vec3(0.0 ,  0.0,  1.0), glm::vec3(0.0, -1.0,  0.0)),
	huongToi * glm::lookAt(vtSang, vtSang + glm::vec3(0.0 ,  0.0, -1.0), glm::vec3(0.0, -1.0,  0.0))
	};
	shaderKhoi.KichHoat();
	glUniformMatrix4fv(glGetUniformLocation(shaderKhoi.ID, "matran[0]"), 1, GL_FALSE, glm::value_ptr(chuyenToi[0]));
	glUniformMatrix4fv(glGetUniformLocation(shaderKhoi.ID, "matran[1]"), 1, GL_FALSE, glm::value_ptr(chuyenToi[1]));
	glUniformMatrix4fv(glGetUniformLocation(shaderKhoi.ID, "matran[2]"), 1, GL_FALSE, glm::value_ptr(chuyenToi[2]));
	glUniformMatrix4fv(glGetUniformLocation(shaderKhoi.ID, "matran[3]"), 1, GL_FALSE, glm::value_ptr(chuyenToi[3]));
	glUniformMatrix4fv(glGetUniformLocation(shaderKhoi.ID, "matran[4]"), 1, GL_FALSE, glm::value_ptr(chuyenToi[4]));
	glUniformMatrix4fv(glGetUniformLocation(shaderKhoi.ID, "matran[5]"), 1, GL_FALSE, glm::value_ptr(chuyenToi[5]));
	glUniform3f(glGetUniformLocation(shaderKhoi.ID, "vtDen"), vtSang.x, vtSang.y, vtSang.z);
	glUniform1f(glGetUniformLocation(shaderKhoi.ID, "tamXa"), tamXa);

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
				tieuDe = "Chieu sang huong toi - " + fps + " FPS / " + ms + " ms";
			glfwSetWindowTitle(window, tieuDe.c_str());
			tdt = tdht; dem = 0;
		}
		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, bongToi, bongToi);
		diemFbo.Bind();
		glClear(GL_DEPTH_BUFFER_BIT);
		banDo.Ve(shaderKhoi, gocNhin);
		diemFbo.Unbind();

		glViewport(0, 0, doRong, doCao);
		fbo.Bind();
		glClearColor(pow(0.83f, gamma), pow(0.42f, gamma), pow(0.1f, gamma), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDisable(GL_CULL_FACE);

		gocNhin.Inputs(window);
		gocNhin.CapNhat(45.0f, 0.1f, tamXa);
		chuongTrinh.KichHoat();
		glUniformMatrix4fv(glGetUniformLocation(chuongTrinh.ID, "denChieu"), 1, GL_FALSE, glm::value_ptr(chieuSang));
		glUniform1f(glGetUniformLocation(chuongTrinh.ID, "tamXa"), tamXa);
		khoiKhungAnh.Bind(2, GL_TEXTURE_CUBE_MAP);
		glUniform1i(glGetUniformLocation(chuongTrinh.ID, "khoiToi"), 2);

		banDo.Ve(chuongTrinh, gocNhin);
		khungFbo.Bind(fbo, doRong, doCao);
		fbo.Unbind();
		shaderKhung.KichHoat();

		vao.Bind();
		glDisable(GL_DEPTH_TEST);
		khungAnh.Bind();
		hinhAnh.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	chuongTrinh.Xoa();
	shaderKhung.Xoa();
	shaderToi.Xoa();
	hinhAnh.Xoa();
	khungAnh.Xoa();
	khoiKhungAnh.Xoa();

	vao.Xoa();
	vbo.Xoa();
	rbo.Xoa();
	fbo.Xoa();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}