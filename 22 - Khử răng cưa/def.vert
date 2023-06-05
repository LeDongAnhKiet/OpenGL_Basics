#version 330 core

layout (location = 0) in vec3 aVt;
layout (location = 1) in vec3 aBthg;
layout (location = 2) in vec3 aMau;
layout (location = 3) in vec2 aTex;

out vec3 vtht, bThg, mauSac;
out vec2 txCrd;
uniform mat4 camMat, mohinh, dichchuyen, xoay, kichthuoc;

void main()
{
	vtht = vec3(mohinh * dichchuyen * -xoay * kichthuoc * vec4(aVt, 1.0f));
	bThg = aBthg;
	mauSac = aMau;
	txCrd = mat2(0.0, -2.0, 1.0, 0.0) * aTex;
	gl_Position = camMat * vec4(vtht, 1.0);
}