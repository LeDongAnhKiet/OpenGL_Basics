#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec3 aClr;
layout (location = 3) in vec2 aTex;

out vec3 vtht, bThg, mauSac;
out vec2 txCrd;
uniform mat4 camMat, mohinh;

void main()
{
	vtht = vec3(mohinh * vec4(aPos, 1.0f));
	bThg = aNorm;
	mauSac = aClr;
	txCrd = aTex;
	gl_Position = camMat * vec4(vtht, 1.0);

}