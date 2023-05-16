#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_content(const char* file);

class Shader
{
public:
	// tham chiếu vào Shader
	GLuint ID;
	// khởi tạo Shader = 2 file
	Shader(const char* vertexFile, const char* fragmentFile);

	// kích hoạt Shader
	void Activate();
	// xóa Shader
	void Delete();
};

#endif