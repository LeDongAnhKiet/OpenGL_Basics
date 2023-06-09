#version 330 core

in vec4 vtFrag;
uniform vec3 vtDen;
uniform float tamXa;

void main()
{
	gl_FragDepth = length(vtFrag.xyz - vtDen) / tamXa;
}