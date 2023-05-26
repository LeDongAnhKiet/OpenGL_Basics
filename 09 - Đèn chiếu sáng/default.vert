#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aClr;
layout (location = 2) in vec2 aTex;
// toa do chua duoc binh thuong hoa
layout (location = 3) in vec3 aNorm;

out vec3 mauSac;
out vec2 txCrd;
// xuat toa do thuong cho Fragment shader
out vec3 bThg;
out vec3 vtht;

// nhap ma tran camera tu ham chinh
uniform mat4 camMat;
uniform mat4 mohinh;

void main()
{
	vtht = vec3(mohinh * vec4(aPos, 1.0f));
	gl_Position = camMat * vec4(vtht, 1.0);
	mauSac = aClr;
	txCrd = aTex;
	bThg = aNorm;
}