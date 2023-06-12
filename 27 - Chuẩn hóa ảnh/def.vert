#version 330 core

layout (location = 0) in vec3 aVt;
layout (location = 1) in vec3 aBthg;
layout (location = 2) in vec3 aMau;
layout (location = 3) in vec2 aTex;

out DATA
{
	vec3 chuan, mauSac, den, cam;
	vec2 txCrd;
	mat4 chieu, mohinh;
} xuat;
uniform mat4 camMat, mohinh, dichchuyen, xoay, kichthuoc, denChieu;
uniform vec3 vtDen, vtCam;

void main()
{
	gl_Position = mohinh * dichchuyen * -xoay * kichthuoc * vec4(aVt, 1.0f);
	xuat.chuan = aBthg;
	xuat.mauSac = aMau;
	xuat.txCrd = aTex;
	xuat.chieu = camMat;
	xuat.mohinh = mohinh * dichchuyen * -xoay * kichthuoc;
	xuat.den = vtDen;
	xuat.cam = vtCam;
}