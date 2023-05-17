#version 330 core

out vec4 FragColor;
in vec3 color;
// nhap toa do anh tu Vertex Shader
in vec2 txCrd;
// lay don vi anh tu ham chinh
uniform sampler2D tex;

void main()
{
	FragColor = texture(tex, txCrd);
}
