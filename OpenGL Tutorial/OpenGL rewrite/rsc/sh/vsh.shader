#version 330 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_colour;
layout(location = 2) in vec3 normal;

uniform vec3 ambientLight;
uniform vec3 lightPosition;

uniform mat4 fullTransformMatrix;
uniform mat4 modelToWorldTransformationMatrix;

out vec3 theNormal;
out vec3 thePosition;

void main()
{
	vec4 v = vec4(vertex_position, 1.0);
	gl_Position = fullTransformMatrix * v;
	theNormal = vec3(modelToWorldTransformationMatrix * vec4(normal, 0));
	thePosition = vec3(modelToWorldTransformationMatrix * v);
}