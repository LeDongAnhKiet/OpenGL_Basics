#include "Model.h"

const GLuint doRong = 800, doCao = 800;
// đỉnh các điểm
GLfloat dinh[] =
{
	//	tọa độ điểm
	-1.0f, -1.0f,  1.0f,	//	    7--------6
	 1.0f, -1.0f,  1.0f,	//	   /|       /|
	 1.0f, -1.0f, -1.0f,	//	  4--------5 |
	-1.0f, -1.0f, -1.0f,	//	  | |      | |
	-1.0f,  1.0f,  1.0f,	//	  | 3------|-2
	 1.0f,  1.0f,  1.0f,	//	  |/       |/
	 1.0f,  1.0f, -1.0f,	//	  0--------1
	-1.0f,  1.0f, -1.0f
};
// chỉ số điểm
GLuint chiso[] =
{
	// mặt phải
	1, 2, 6,
	6, 5, 1,
	// mặt trái
	0, 4, 7,
	7, 3, 0,
	// mặt trên
	4, 5, 6,
	6, 7, 4,
	// mặt đáy
	0, 3, 2,
	2, 1, 0,
	// mặt khuất
	0, 1, 5,
	5, 4, 0,
	//mặt chính diện
	3, 7, 6,
	6, 2, 3
};

float rndf(float max = 2.0f) { return -1.0f + (rand() / (RAND_MAX / max)); }

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(doRong, doCao, "Cubemap & Skybox", NULL, NULL);
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
	Shader shaderTroi("troi.vert", "troi.frag");
	Shader shaderThach("thach.vert", "def.frag");
	Shader shaderWins("thach.vert", "wins.frag");
	glm::vec4 mauSang = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 vtSang = glm::vec3(0.5f, 0.5f, 0.5f);

	chuongTrinh.KichHoat();
	glUniform4f(glGetUniformLocation(chuongTrinh.ID, "mauDen"), mauSang.x, mauSang.y, mauSang.z, mauSang.w);
	glUniform3f(glGetUniformLocation(chuongTrinh.ID, "vtDen"), vtSang.x, vtSang.y, vtSang.z);
	shaderTroi.KichHoat();
	glUniform1i(glGetUniformLocation(shaderTroi.ID, "troi"), 0);
	shaderThach.KichHoat();
	glUniform4f(glGetUniformLocation(shaderThach.ID, "mauDen"), mauSang.x, mauSang.y, mauSang.z, mauSang.w);
	glUniform3f(glGetUniformLocation(shaderThach.ID, "vtDen"), vtSang.x, vtSang.y, vtSang.z);
	shaderWins.KichHoat();
	glUniform4f(glGetUniformLocation(shaderWins.ID, "mauDen"), mauSang.x, mauSang.y, mauSang.z, mauSang.w);
	glUniform3f(glGetUniformLocation(shaderWins.ID, "vtDen"), vtSang.x, vtSang.y, vtSang.z);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	GocNhin gocNhin(doRong, doCao, glm::vec3(0.0f, 0.1f, 2.0f));
	MoHinh mayBay("models/airplane/scene.gltf");
	VAO vao = VAO();
	VBO vbo = VBO(dinh, sizeof(dinh));
	EBO ebo = EBO(chiso, sizeof(chiso));

	vao.LinkAttr(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
	// các mặt hình lập phương
	const char* lapPhuong[6] =
	{
		"sky_right.jpg",
		"sky_left.jpg",
		"sky_top.jpg",
		"sky_bottom.jpg",
		"sky_front.jpg",
		"sky_back.jpg"
	};
	HinhAnh bauTroi = HinhAnh(lapPhuong);

	// số thiên thạch
	const GLuint n = 1500;
	// phạm vi (rad) và độ lệch
	float phamVi = 50.0f, doLech = 30.0f;
	std::vector <glm::mat4> maTran;
	for (GLuint i = 0; i < n; i++)
	{
		// khởi tạo x, y cho hàm x^2 + y^2 = rad^2, tạo ra hình tròn
		float _x = rndf(), _y = ((rand() % 2) * 2 - 1),
			vungCuoi = phamVi + rndf() * doLech;
		glm::vec3 dichChuyen, kichThuoc;
		glm::quat xoay;

		// phân tán ngẫu nhiên đều nhau
		if (rndf() > 0.5f) dichChuyen = glm::vec3(_y * vungCuoi, rndf(), _x * vungCuoi);
		// dịch chuyển sao cho gần với phạm vi hình tròn
		else dichChuyen = glm::vec3(_x * vungCuoi, rndf(), _y * vungCuoi);
		// xoay ngẫu nhiên
		xoay = glm::quat(1.0f, rndf(), rndf(), rndf());
		// đổi kich thước ngẫu nhiên
		kichThuoc = 0.1f * glm::vec3(rndf(), rndf(), rndf());

		// khởi tạo các ma trận
		glm::mat4 dc, x, kt = dc = x = glm::mat4(1.0f);
		// biến đổi các ma trận đó
		dc = glm::translate(dc, dichChuyen);
		x = glm::mat4_cast(xoay);
		kt = glm::scale(kt, kichThuoc);
		maTran.push_back(dc * x * kt);
	}
	MoHinh thienThach("models/asteroid/scene.gltf", n, maTran);
	for (GLuint i = 0; i < n * 2; i++)
	{
		// khởi tạo x, y cho hàm x^2 + y^2 = rad^2, tạo ra hình tròn
		float _x = rndf(3.0f), _y = ((rand() % 2) * 2 - 1),
			vungCuoi = phamVi + rndf(3.0f) * doLech;
		glm::vec3 dichChuyen, kichThuoc;
		glm::quat xoay;

		// phân tán ngẫu nhiên đều nhau
		if (rndf(3.0f) > 0.5f) dichChuyen = glm::vec3(_y * vungCuoi, rndf(), _x * vungCuoi);
		// dịch chuyển sao cho gần với phạm vi hình tròn
		else dichChuyen = glm::vec3(_x * vungCuoi, rndf(3.0f), _y * vungCuoi);
		// xoay ngẫu nhiên
		xoay = glm::quat(1.0f, rndf(3.0f), rndf(3.0f), rndf(3.0f));
		// đổi kich thước ngẫu nhiên
		kichThuoc = 0.1f * glm::vec3(rndf(3.0f), rndf(3.0f), rndf(3.0f));

		// khởi tạo các ma trận
		glm::mat4 dc, x, kt = dc = x = glm::mat4(1.0f);
		// biến đổi các ma trận đó
		dc = glm::translate(dc, dichChuyen);
		x = glm::mat4_cast(xoay);
		kt = glm::scale(kt, kichThuoc);
		maTran.push_back(dc * x * kt);
	}
	MoHinh windows("models/windows/scene.gltf", n * 2, maTran);

	while (!glfwWindowShouldClose(window))
	{
		double tdt = 0.0, tdht = 0.0, ktg;
		tdht = glfwGetTime(); ktg = tdht - tdt;
		GLuint dem = 0; dem++;
		if (ktg >= 1.0 / 30.0)
		{
			std::string fps = std::to_string((1.0 / ktg) * dem),
				ms = std::to_string((ktg / dem) * 1000),
				tieuDe = "Nen bau troi - " + fps + " FPS / " + ms + " ms";
			glfwSetWindowTitle(window, tieuDe.c_str());
			tdt = tdht; dem = 0;
		}
		glClearColor(0.83f, 0.42f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		gocNhin.Inputs(window);
		gocNhin.CapNhat(45.0f, 0.1f, 100.0f);
		mayBay.Ve(chuongTrinh, gocNhin);
		thienThach.Ve(shaderThach, gocNhin);
		windows.Ve(shaderWins, gocNhin);

		// mặc định nền 3D có chiều sâu = 1.0, thêm dấu = để ảnh ko bị mất
		glDepthFunc(GL_LEQUAL);
		shaderTroi.KichHoat();
		glm::mat4 view = glm::mat4(1.0f), proj = view;
		// đổi từ mat4 -> mat3 -> mat4 lại để bỏ dòng cột cuối, nó có ảnh hưởng đển ảnh (chúng ta ko muốn điều đó)
		view = glm::mat4(glm::mat3(glm::lookAt(gocNhin.ViTri, gocNhin.ViTri + gocNhin.Huong, gocNhin.Len)));
		proj = glm::perspective(glm::radians(45.0f), (float)doRong / doCao, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(shaderTroi.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shaderTroi.ID, "proj"), 1, GL_FALSE, glm::value_ptr(proj));

		vao.Bind();
		bauTroi.Bind3D();
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		vao.Unbind();
		glDepthFunc(GL_LESS);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	chuongTrinh.Xoa();
	shaderTroi.Xoa();
	shaderThach.Xoa();
	shaderWins.Xoa();
	bauTroi.Xoa();

	vao.Xoa();
	vbo.Xoa();
	ebo.Xoa();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}