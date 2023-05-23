#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.h"

class GocNhin
{
public:
	// 3 véctơ của Góc nhìn: vị trí, hướng x,y và hướng z
	glm::vec3 ViTri,
		Huong = glm::vec3(0.0f, 0.0f, -1.0f),
		Len = glm::vec3(0.0f, 1.0f, 0.0f);
	// ngăn ngừa việc Góc nhìn nhảy lung tung khi nhấn chuột
	bool ThaChuot = true;
	// độ rộng và cao của Góc nhìn
	int Rong, Cao;
	float TocDo = 0.1f, DoNhay = 100.0f;

	// khởi tạo Góc nhìn
	GocNhin(int r, int c, glm::vec3 vt);
	void MaTran(float fovDeg, float gan, float xa, Shader& shader, const char* unif);
	void Inputs(GLFWwindow* win);
};
#endif