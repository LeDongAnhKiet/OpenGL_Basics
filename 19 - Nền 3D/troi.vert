#version 330 core

layout (location = 0) in vec3 aVt;
out vec3 txCrd;
uniform mat4 proj, view;

void main()
{
	vec4 vt = proj * view * vec4(aVt, 1.0f);
	gl_Position = vec4(vt.x, vt.y, vt.w, vt.w);
	txCrd = vec3(aVt.x, aVt.y, -aVt.z);
}