#version 330 core

out vec4 MauFrag;
in vec3 txCrd;
uniform samplerCube troi;

void main()
{
	MauFrag = texture(troi, txCrd);
}