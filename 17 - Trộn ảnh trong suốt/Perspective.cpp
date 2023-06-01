#include"Perspective.h"
using namespace glm;

GocNhin::GocNhin(int r, int c, glm::vec3 vt)
{
	Rong = r, Cao = c, ViTri = vt;
}

void GocNhin::CapNhat(float FOVdeg, float tamGan, float tamXa)
{
	mat4 view = mat4(1.0f);
	mat4 proj = mat4(1.0f);
	view = lookAt(ViTri, ViTri + Huong, Len);
	proj = perspective(radians(FOVdeg), (float)Rong / Cao, tamGan, tamXa);
	MaTran = proj * view;
}

void GocNhin::Xuat(Shader& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, value_ptr(MaTran));
}

void GocNhin::Inputs(GLFWwindow* win)
{
	if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
		ViTri += TocDo / 5 * Huong;
	if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
		ViTri -= TocDo / 5 * normalize(cross(Huong, Len));
	if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
		ViTri -= TocDo / 5 * Huong;
	if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
		ViTri += TocDo / 5 * normalize(cross(Huong, Len));
	if (glfwGetKey(win, GLFW_KEY_E) == GLFW_PRESS)
		ViTri -= TocDo / 5 * Len;
	if (glfwGetKey(win, GLFW_KEY_Q) == GLFW_PRESS)
		ViTri += TocDo / 5 * Len;
	if (glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		TocDo = 0.5f;
	if (glfwGetKey(win, GLFW_KEY_R) == GLFW_PRESS)
		ViTri = vec3(0.0f, 0.1f, 2.0f),
		Huong = vec3(0.0f, 0.0f, -1.0f),
		Len = vec3(0.0f, 1.0f, 0.0f);
	else if (glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		TocDo = 0.1f;
	if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		if (ThaChuot)
		{
			glfwSetCursorPos(win, (Rong / 2.0), (Cao / 2.0));
			ThaChuot = false;
		}
		double chuotX, chuotY;
		glfwGetCursorPos(win, &chuotX, &chuotY);
		float xoayX = DoNhay * (float)(chuotY - (Cao / 2.0)) / Cao,
			xoayY = DoNhay * (float)(chuotX - (Rong / 2.0)) / Rong;
		vec3 huong = rotate(Huong, radians(-xoayX), normalize(cross(Huong, Len)));
		if (abs(angle(huong, Len) - radians(95.0f)) <= radians(80.0f))
			Huong = huong;
		Huong = rotate(Huong, radians(-xoayY), Len);
		glfwSetCursorPos(win, (Rong / 2.0), (Cao / 2.0));
	}
	else if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		ThaChuot = true;
	}
}