#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

out vec3 bThg, mauSac;
out vec2 txCrd;

in DATA
{
	vec3 bThg, mauSac;
	vec2 txCrd;
	mat4 proj;
} nhap[];

vec4 bungNo(int no)
{
	vec3 v1 = vec3(gl_in[0].gl_Position - gl_in[1].gl_Position),
		v2 = vec3(gl_in[2].gl_Position - gl_in[1].gl_Position);
	vec4 beMat = vec4(normalize(cross(v1, v2)), 0.0f);
	if (no != 0) return beMat;
	return vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

void main()
{
	gl_Position = nhap[0].proj * (gl_in[0].gl_Position + bungNo(0));
	bThg = nhap[0].bThg;
	mauSac = nhap[0].mauSac;
	txCrd = nhap[0].txCrd;
	EmitVertex();

	gl_Position = nhap[1].proj * (gl_in[1].gl_Position + bungNo(0));
	bThg = nhap[1].bThg;
	mauSac = nhap[1].mauSac;
	txCrd = nhap[1].txCrd;
	EmitVertex();

	gl_Position = nhap[2].proj * (gl_in[2].gl_Position + bungNo(0));
	bThg = nhap[2].bThg;
	mauSac = nhap[2].mauSac;
	txCrd = nhap[2].txCrd;
	EmitVertex();

	EndPrimitive();
}