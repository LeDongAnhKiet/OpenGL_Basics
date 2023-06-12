#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

out vec3 bThg, mauSac, vtDen, vtCam, vtht;
out vec2 txCrd;

in DATA
{
	vec3 chuan, mauSac, den, cam;
	vec2 txCrd;
	mat4 chieu, mohinh;
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
	vec3 canh1 = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz,
		canh2 = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
	vec2 deltaUV1 = nhap[1].txCrd - nhap[0].txCrd,
		deltaUV2 = nhap[2].txCrd - nhap[0].txCrd;
	float invDet = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
	vec3 tiepTuyen = vec3(invDet * (deltaUV2.y * canh1 - deltaUV1.y * canh2)),
		biTiepTuyen = vec3(invDet * (deltaUV1.x * canh1 - deltaUV2.x * canh2));

	vec3 T = normalize(vec3(nhap[0].mohinh * vec4(tiepTuyen, 0.0f))),
		B = normalize(vec3(nhap[0].mohinh * vec4(biTiepTuyen, 0.0f))),
		C = normalize(vec3(nhap[0].mohinh * vec4(cross(canh2, canh1), 0.0f)));
	mat3 TBC = mat3(T, B, C);
	TBC = transpose(TBC);

	gl_Position = nhap[0].chieu * (gl_in[0].gl_Position + bungNo(0));
	bThg = nhap[0].chuan;
	mauSac = nhap[0].mauSac;
	txCrd = nhap[0].txCrd;
	vtht = TBC * gl_in[0].gl_Position.xyz;
	vtDen = TBC * nhap[0].den;
	vtCam = TBC * nhap[0].cam;
	EmitVertex();

	gl_Position = nhap[1].chieu * (gl_in[1].gl_Position + bungNo(0));
	bThg = nhap[1].chuan;
	mauSac = nhap[1].mauSac;
	txCrd = nhap[1].txCrd;
	vtht = TBC * gl_in[1].gl_Position.xyz;
	vtDen = TBC * nhap[1].den;
	vtCam = TBC * nhap[1].cam;
	EmitVertex();

	gl_Position = nhap[2].chieu * (gl_in[2].gl_Position + bungNo(0));
	bThg = nhap[2].chuan;
	mauSac = nhap[2].mauSac;
	vtht = TBC * gl_in[2].gl_Position.xyz;
	txCrd = nhap[2].txCrd;
	vtDen = TBC * nhap[2].den;
	vtCam = TBC * nhap[2].cam;
	EmitVertex();

	EndPrimitive();
}