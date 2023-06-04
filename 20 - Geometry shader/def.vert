#version 330 core

layout (location = 0) in vec3 aVt;
layout (location = 1) in vec3 aBthg;
layout (location = 2) in vec3 aMau;
layout (location = 3) in vec2 aTx;

out DATA
{
	vec3 bThg, mauSac;
	vec2 txCrd;
	mat4 proj;
} xuat;
out vec3 vtht;
uniform mat4 camMat, mohinh, dichchuyen, xoay, kichthuoc;

void main()
{
	gl_Position = mohinh * dichchuyen * xoay * kichthuoc * vec4(aVt, 1.0f);
	xuat.bThg = aBthg;
	xuat.mauSac = aMau;
	xuat.txCrd = mat2(0.0, -1.0, 1.0, 0.0) * aTx;
	xuat.proj = camMat;
}