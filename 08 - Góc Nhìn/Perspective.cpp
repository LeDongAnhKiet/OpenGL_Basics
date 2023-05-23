#include "Perspective.h"
using namespace glm;

GocNhin::GocNhin(int r, int c, vec3 vt)
{
	Rong = r;
	Cao = c;
	ViTri = vt;
}

void GocNhin::MaTran(float fovDeg, float gan, float xa, Shader& shader, const char* unif)
{
	// khởi tạo ma trận để ko bị null
	mat4 view = mat4(1.0f);
	mat4 proj = mat4(1.0f);
	// gán giá trị để Góc nhìn đúng vị trí, đúng hướng
	view = lookAt(ViTri, ViTri + Huong, Len);
	// thêm cảnh quan vào góc nhìn
	proj = perspective(radians(fovDeg), (float)Rong / Cao, gan, xa);
	// xuất ma trận góc nhìn vào Vertex Shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, unif), 1, GL_FALSE, value_ptr(proj * view));
}

void GocNhin::Inputs(GLFWwindow* win)
{
	// Xử lí bàn phím
	if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
		ViTri += TocDo / 50 * -Len;
	if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
		ViTri += TocDo / 50 * normalize(cross(Huong, Len));
	if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
		ViTri += TocDo / 50 * Len;
	if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
		ViTri += TocDo / 50 * -normalize(cross(Huong, Len));
	if (glfwGetKey(win, GLFW_KEY_Q) == GLFW_PRESS)
		ViTri += TocDo / 50 * -Huong;
	if (glfwGetKey(win, GLFW_KEY_E) == GLFW_PRESS)
		ViTri += TocDo / 50 * Huong;
	if (glfwGetKey(win, GLFW_KEY_F) == GLFW_PRESS)
		TocDo = 0.52f;
	if (glfwGetKey(win, GLFW_KEY_R) == GLFW_PRESS)
		ViTri = vec3(0.0f, 0.25f, 2.0f),
		Huong = vec3(0.0f, 0.0f, -1.0f),
		Len = vec3(0.0f, 1.0f, 0.0f);
	else if (glfwGetKey(win, GLFW_KEY_F) == GLFW_RELEASE)
		TocDo = 0.1f;
	// xử lí chuột
	if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// giấu con trỏ chuột 
		glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		// tránh việc nhảy lung tung của góc nhìn khi nhấn chuột
		if (ThaChuot)
		{
			glfwSetCursorPos(win, (Rong / 2.0), (Cao / 2.0));
			// đã nhấn chuột
			ThaChuot = false;
		}
		// tọa độ của con trỏ chuột
		double chuotX, chuotY;
		// lấy tọa độ con trỏ
		glfwGetCursorPos(win, &chuotX, &chuotY);
		// chỉnh vị trí con trỏ vào giữa window và đổi sang góc độ
		float xoayX = DoNhay * (float)(chuotY - (Cao / 2.0)) / Cao,
			xoayY = DoNhay * (float)(chuotX - (Rong / 2.0)) / Rong;
		// tính tọa độ sẽ đổi tiếp theo của hướng
		vec3 huong = rotate(Huong, radians(xoayX), normalize(cross(Huong, Len)));
		// xác định hướng tiếp theo có hợp lý ko
		if (abs(angle(huong, Len) - radians(95.0f)) <= radians(80.0f))
			Huong = huong;
		// đổi hướng góc nhìn theo hướng chuột
		Huong = rotate(Huong, radians(xoayY), Len);
		// gán tọa độ con trỏ vào giữa window để nó ko chạy xa
		glfwSetCursorPos(win, (Rong / 2.0), (Cao / 2.0));
	}
	else if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// hiện con trỏ chuột khi thả chuột
		glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// đã thả chuột
		ThaChuot = true;
	}
}