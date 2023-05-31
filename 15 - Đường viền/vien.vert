#version 330 core

layout (location = 0) in vec3 aVt;
layout (location = 1) in vec3 aBthg;

uniform mat4 camMat, mohinh, dichchuyen, xoay, kichthuoc;
uniform float vien;

void main()
{
	vec3 vtht = vec3(mohinh * dichchuyen * -xoay * kichthuoc * vec4(aVt + aBthg * vien, 1.0f));
	gl_Position = camMat * vec4(vtht, 1.0);
}