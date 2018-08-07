#version 330 core

in vec2 texture_coords;
out vec4 final_fragment_colour;

uniform sampler2D image;
uniform vec3 sprite_colour;

void main()
{
	final_fragment_colour = vec4(sprite_colour, 1.0f) * texture(image, texture_coords);
}