#version 330 core

layout (location = 0) in vec2 aVt;
layout (location = 1) in vec2 aTx;

out vec2 txCrd;

void main()
{
	gl_Position = vec4(aVt.x, aVt.y, 0.0, 1.0);
	txCrd = aTx;
}