#include "textureLoader.h"

std::map<std::string, GLabs::Texture> TextureLoader::Textures;

GLabs::Texture TextureLoader::LoadTexture(const GLchar* p_file, GLboolean p_alpha, std::string p_name)
{
	Textures[p_name] = LoadTextureFromFile(p_file, p_alpha);
	return Textures[p_name];
}

GLabs::Texture TextureLoader::GetTexture(std::string p_name)
{
	return Textures[p_name];
}

void TextureLoader::Clear()
{
	for (auto iter : Textures) glDeleteTextures(1, &iter.second.textureID);
}

GLabs::Texture TextureLoader::LoadTextureFromFile(const GLchar* p_file, GLboolean p_alpha)
{
	GLabs::Texture texture;
	if (p_alpha)
	{
		texture.textureFormat = GL_RGBA;
		texture.imageFormat = GL_RGBA;
	}
	int width, height;
	unsigned char* image = stbi_load(p_file, &width, &height, 0, texture.imageFormat == GL_RGBA ? 4 : 3);
	texture.Generate(width, height, image);
	stbi_image_free(image);
	return texture;
}