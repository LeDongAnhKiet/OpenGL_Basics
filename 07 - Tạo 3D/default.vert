#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

out vec3 color;
out vec2 txCrd;
uniform float scale;

// nhap cac ma tran can thiet de xem voi phuong dien 3D
uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;

void main()
{
	// xuat cac vi tri / toa do cac diem
	gl_Position = view * proj * model * vec4(aPos, 1.0);
	color = aColor;
	txCrd = aTex;
}