#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
// toa do hinh anh
layout (location = 2) in vec2 aTex;

out vec3 color;
// xuat toa do hinh anh den fragment shader
out vec2 txCrd;
uniform float scale;

void main()
{
	// vi tri / toa do cac diem
	gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
	// gan mau tu Vertex Data thanh "color"
	color = mix(aColor, vec3(2.0) - aColor, - aPos.y);
	// gan toa do hinh anh tu Vertex Data den "txCrd"
	txCrd = aTex;
}
