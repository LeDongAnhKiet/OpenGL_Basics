#version 330 core

layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in DATA
{
	vec3 bThg, mauSac;
	vec2 txCrd;
	mat4 proj;
} nhap[];

void main()
{
	gl_Position = nhap[0].proj * gl_in[0].gl_Position;
	EmitVertex();
	gl_Position = nhap[0].proj * (gl_in[0].gl_Position + 0.01f * vec4(nhap[0].bThg, 0.0f));
	EmitVertex();
	EndPrimitive();

	gl_Position = nhap[1].proj * gl_in[1].gl_Position;
	EmitVertex();
	gl_Position = nhap[1].proj * (gl_in[1].gl_Position + 0.01f * vec4(nhap[1].bThg, 0.0f));
	EmitVertex();
	EndPrimitive();

	gl_Position = nhap[2].proj * gl_in[2].gl_Position;
	EmitVertex();
	gl_Position = nhap[2].proj * (gl_in[2].gl_Position + 0.01f * vec4(nhap[2].bThg, 0.0f));
	EmitVertex();
	EndPrimitive();
}