#version 330 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_colour;

out vec3 pass_vertex_colour;

void main()
{
	gl_Position = vec4(vertex_position, 1.0);
	pass_vertex_colour = vertex_colour;
}