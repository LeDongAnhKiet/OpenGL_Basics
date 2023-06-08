#version 330 core

layout (location = 0) in vec3 aVt;
uniform mat4 denChieu, mohinh;

void main()
{
	gl_Position = denChieu * mohinh * vec4(aVt, 1.0);
}