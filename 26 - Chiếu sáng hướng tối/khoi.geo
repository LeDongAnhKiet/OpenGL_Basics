#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 18) out;

uniform mat4 matran[6];
out vec4 vtFrag;

void main()
{
	for (int mat; mat < 6; ++mat)
	{
		gl_Layer = mat;
		for (int i = 0; i < 3; i++)
		{
			vtFrag = gl_in[i].gl_Position;
			gl_Position = matran[mat] * vtFrag;
			EmitVertex();
		}
		EndPrimitive();
	}
}