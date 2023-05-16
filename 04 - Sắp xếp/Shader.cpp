#include "Shader.h"
using namespace std;

// đọc file
string get_content(const char* file)
{
	ifstream input(file, ios::binary);
	if (!input) throw(errno);
	string contents;
	input.seekg(0, ios::end);
	contents.resize(input.tellg());
	input.seekg(0, ios::beg);
	input.read(&contents[0], contents.size());
	input.close();
	return(contents);
	
}

Shader::Shader(const char* vertFile, const char* fragFile)
{
	// lưu trữ thành string
	string vert = get_content(vertFile);
	string frag = get_content(fragFile);

	// chuyển đổi từ string thành char động
	const char* vertSrc = vert.c_str();
	const char* fragSrc = frag.c_str();

	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertSrc, NULL);
	glCompileShader(vertShader);

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragSrc, NULL);
	glCompileShader(fragShader);

	ID = glCreateProgram();
	glAttachShader(ID, vertShader);
	glAttachShader(ID, fragShader);
	glLinkProgram(ID);

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

}

void Shader::Activate() { glUseProgram(ID); }

void Shader::Delete() { glDeleteProgram(ID); }