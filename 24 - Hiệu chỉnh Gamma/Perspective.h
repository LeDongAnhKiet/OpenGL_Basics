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
	glm::vec3 ViTri, Huong = glm::vec3(0.0f, 0.0f, -1.0f);
	const glm::vec3 Len = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 MaTran = glm::mat4(1.0f);

	bool ThaChuot = true;
	int Rong, Cao;
	float TocDo = 0.1f, DoNhay = 100.0f;

	GocNhin(int r, int c, glm::vec3 vt);
	void CapNhat(float FOVdeg, float nearPlane, float farPlane);
	void Xuat(Shader& shader, const char* uniform);
	void Inputs(GLFWwindow* win);
};
#endif