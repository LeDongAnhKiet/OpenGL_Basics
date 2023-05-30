#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

out vec3 vtht, bThg, mauSac;
out vec2 txCrd;
// nhap cac bien doi ma tran tu ham chinh
uniform mat4 camMat, mohinh, dichchuyen, xoay, kichthuoc;

void main()
{
	vtht = vec3(mohinh * dichchuyen * -xoay * kichthuoc * vec4(aPos, 1.0f));
	bThg = aNormal;
	mauSac = aColor;
	txCrd = mat2(0.0, -1.0, 1.0, 0.0) * aTex;
	gl_Position = camMat * vec4(vtht, 1.0);
}