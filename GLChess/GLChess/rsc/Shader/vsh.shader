#version 330 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_colour;
layout(location = 2) in float x_offset;
layout(location = 3) in float y_offset;

out vec3 pass_vertex_colour;

void main()
{
	gl_Position = vec4(vertex_position.x + x_offset, vertex_position.y + y_offset, vertex_position.z, 1.0f);
	pass_vertex_colour = vertex_colour;
}