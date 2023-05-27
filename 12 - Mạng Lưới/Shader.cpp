#include "Shader.h"
using namespace std;

string get_content(const char* file)
{
	ifstream input(file, ios::binary);
	if (input)
	{
		string cont;
		input.seekg(0, ios::end);
		cont.resize(input.tellg());
		input.seekg(0, ios::beg);
		input.read(&cont[0], cont.size());
		input.close();
		return cont;
	}
	throw(errno);
}

Shader::Shader(const char* vertFile, const char* fragFile)
{
	string vert = get_content(vertFile);
	string frag = get_content(fragFile);

	const char* vertSrc = vert.c_str();
	const char* fragSrc = frag.c_str();

	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertSrc, NULL);
	glCompileShader(vertShader);
	KtLoi(vertShader, "DIEM");

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragSrc, NULL);
	glCompileShader(fragShader);
	KtLoi(fragShader, "MANH");

	ID = glCreateProgram();
	glAttachShader(ID, vertShader);
	glAttachShader(ID, fragShader);
	glLinkProgram(ID);
	KtLoi(ID, "CHUONG TRINH");

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

}

void Shader::KichHoat() { glUseProgram(ID); }

void Shader::Xoa() { glDeleteProgram(ID); }

void Shader::KtLoi(unsigned int shader, const char* type)
{
	GLint compiled;
	char log[1024];
	if (type != "CHUONG TRINH")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (compiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, log);
			cout << "LOI BIEN DICH SHADER: " << type << "\n" << log << endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &compiled);
		if (compiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, log);
			cout << "LOI KET NOI SHADER: " << type << "\n" << log << endl;
		}
	}
}