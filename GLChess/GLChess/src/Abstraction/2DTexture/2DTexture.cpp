#include "2DTexture.h"

void GLabs::Texture::Generate(GLuint p_width, GLuint p_height, unsigned char* p_data)
{
	width = p_width;
	height = p_height;

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, p_data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void GLabs::Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}