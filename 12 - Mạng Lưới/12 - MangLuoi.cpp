#include "Mesh.h"

const unsigned int doRong = 800, doCao = 800;
// các tọa độ điểm
ToaDo diem[] =
{ //			Vị trí			  /			  Màu sắc		   /		  Kết cấu			/		 Thường			//
	ToaDo{ glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
	ToaDo{ glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },
	ToaDo{ glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
	ToaDo{ glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f) }
};
// các thứ tự điểm
GLuint thutu[] =
{
	 0,  1,  2,
	 0,  2,  3
};
// các tọa độ điểm sáng
ToaDo diemSang[] =
{
	ToaDo{ glm::vec3(-0.1f, -0.1f,  0.1f) },
	ToaDo{ glm::vec3(-0.1f, -0.1f, -0.1f) },
	ToaDo{ glm::vec3( 0.1f, -0.1f, -0.1f) },
	ToaDo{ glm::vec3( 0.1f, -0.1f,  0.1f) },
	ToaDo{ glm::vec3(-0.1f,  0.1f,  0.1f) },
	ToaDo{ glm::vec3(-0.1f,  0.1f, -0.1f) },
	ToaDo{ glm::vec3( 0.1f,  0.1f, -0.1f) },
	ToaDo{ glm::vec3( 0.1f,  0.1f,  0.1f) }
};
// các thứ tự điểm sáng
GLuint thutuSang[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(doRong, doCao, "YoutubeOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Khởi tạo Window thất bại\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, doRong, doCao);

	// các hình ảnh
	HinhAnh hinhAnh[]
	{
		HinhAnh("pop_cat.png", "phanTan", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		HinhAnh("bright.png", "phanChieu", 1, GL_RED, GL_UNSIGNED_BYTE)
	};
	Shader chuongTrinh("default.vert", "default.frag");
	std::vector <ToaDo> td(diem, diem + sizeof(diem) / sizeof(ToaDo));
	std::vector <GLuint> tt(thutu, thutu + sizeof(thutu) / sizeof(GLuint));
	std::vector <HinhAnh> kc(hinhAnh, hinhAnh + sizeof(hinhAnh) / sizeof(HinhAnh));
	// tạo mạng lưới Sàn
	Luoi san(td, tt, kc);

	// tạo shader đèn hình lập phương
	Shader denSang("den.vert", "den.frag");
	// chứa data trong vector vào lưới
	std::vector <ToaDo> ds(diemSang, diemSang + sizeof(diemSang) / sizeof(ToaDo));
	std::vector <GLuint> tts(thutuSang, thutuSang + sizeof(thutuSang) / sizeof(GLuint));
	// tạo mạng lưới Đèn
	Luoi den(ds, tts, kc);

	glm::vec4 mauSang = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 vtSang = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 mhDen = glm::mat4(1.0f);
	mhDen = glm::translate(mhDen, vtSang);
	glm::vec3 vtHinh = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 mHinh = glm::mat4(1.0f);
	mHinh = glm::translate(mHinh, vtHinh);

	denSang.KichHoat();
	glUniformMatrix4fv(glGetUniformLocation(denSang.ID, "mohinh"), 1, GL_FALSE, glm::value_ptr(mhDen));
	glUniform4f(glGetUniformLocation(denSang.ID, "mauDen"), mauSang.x, mauSang.y, mauSang.z, mauSang.w);
	chuongTrinh.KichHoat();
	glUniformMatrix4fv(glGetUniformLocation(chuongTrinh.ID, "mohinh"), 1, GL_FALSE, glm::value_ptr(mHinh));
	glUniform4f(glGetUniformLocation(chuongTrinh.ID, "mauDen"), mauSang.x, mauSang.y, mauSang.z, mauSang.w);
	glUniform3f(glGetUniformLocation(chuongTrinh.ID, "vtDen"), vtSang.x, vtSang.y, vtSang.z);
	glEnable(GL_DEPTH_TEST);
	GocNhin gocNhin(doRong, doCao, glm::vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.15f, 0.02f, 0.18f, 1.5f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		gocNhin.Inputs(window);
		gocNhin.CapNhat(40.0f, 0.1f, 200.0f);
		// vẽ 2 mạng lưới
		san.Ve(chuongTrinh, gocNhin);
		den.Ve(denSang, gocNhin);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	chuongTrinh.Xoa();
	denSang.Xoa();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}