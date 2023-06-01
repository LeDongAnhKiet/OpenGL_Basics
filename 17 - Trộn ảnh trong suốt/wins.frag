#version 330 core

out vec4 MauFrag;
in vec2 txCrd;
uniform sampler2D phanTan;

void main()
{
	if (texture(phanTan, txCrd).a < 0.1) discard;
	MauFrag = texture(phanTan, txCrd);
}