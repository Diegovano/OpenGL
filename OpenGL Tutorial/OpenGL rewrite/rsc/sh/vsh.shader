#version 330 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_colour;

uniform mat4 fullTransformMatrix;

out vec3 pass_vertex_colour;

void main()
{
	vec4 v = vec4(vertex_position, 1.0);
	gl_Position = fullTransformMatrix * v;
	pass_vertex_colour = vertex_colour;
}