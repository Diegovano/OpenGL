#version 330 core

in layout(location = 0) vec3 vertex_position;
in layout(location = 1) vec3 vertex_colour;

uniform mat4 modelTransformMatrix;
uniform mat4 projectionMatrix;

out vec3 pass_vertex_colour;

void main()
{
	vec4 v = vec4(vertex_position, 1.0);
	vec4 newPosition = modelTransformMatrix * v;
	vec4 projectedPosition = projectionMatrix * newPosition;
//	gl_Position = projectedPosition;
	gl_Position = vec4(vertex_position, 1.0);
	pass_vertex_colour = vertex_colour;
}