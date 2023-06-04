#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <fstream>
#include <iostream>

std::string get_content(const char* file);

class Shader
{
public:
	GLuint ID;
	Shader(const char* vertFile, const char* fragFile, const char* geoFile);
	void KichHoat();
	void Xoa();
private:
	void KtLoi(unsigned int shader, const char* type);
};


#endif