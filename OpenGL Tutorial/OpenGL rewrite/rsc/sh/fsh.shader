#version 330 core

in vec3 theNormal;
in vec3 thePosition;

uniform vec3 lightPosition;

out vec4 final_fragment_colour;

void main()
{
	vec3 lightVector = normalize(lightPosition - thePosition);
	float brightness = dot(lightVector, theNormal);
	final_fragment_colour = vec4(brightness, brightness, brightness, 1.0f);
}