#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "Shader.h"

class GocNhin
{
public:
	glm::vec3 ViTri,
		Huong = glm::vec3(0.0f, 0.0f, -1.0f),
		Len = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 MaTran = glm::mat4(1.0f);

	bool ThaChuot = true;
	int Rong, Cao;
	float TocDo = 0.1f, DoNhay = 100.0f;

	GocNhin(int width, int height, glm::vec3 position);

	void CapNhat(float FOVdeg, float tamGan, float tamXa);
	void Xuat(Shader& shader, const char* uniform);
	void Inputs(GLFWwindow* window);
};
#endif