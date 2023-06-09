#version 330 core

layout (location = 0) in vec3 aVt;
uniform mat4 mohinh;

void main()
{
	gl_Position = mohinh * vec4(aVt, 1.0f);
}