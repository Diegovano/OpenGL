#version 330 core

in vec3 pass_vertex_colour;

out vec4 final_fragment_colour;

void main()
{
	final_fragment_colour = vec4(pass_vertex_colour.rgb, 1.0f);
}