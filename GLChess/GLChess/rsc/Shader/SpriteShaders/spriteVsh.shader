#version 330 core

layout(location = 0)in vec4 vertex;

out vec2 texture_coords;

uniform mat4 full_transform_matrix;

void main()
{
	texture_coords = vertex.zw;
	gl_Position = full_transform_matrix * vec4(vertex.xy, -0.5f, 1.0f);
}