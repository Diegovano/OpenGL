#pragma once
#include "../Abstraction/2DTexture/2DTexture.h"
#include <map>
#include <GLEW/include/GL/glew.h>
#include <stb-master/stb_image.h>

class TextureLoader
{
	TextureLoader()
	{

	}
	static GLabs::Texture LoadTextureFromFile(const GLchar* p_file, GLboolean p_alpha);

public:
	static std::map<std::string, GLabs::Texture> Textures;
	static GLabs::Texture LoadTexture(const GLchar* p_file, GLboolean p_alpha, std::string p_name);
	static GLabs::Texture GetTexture(std::string p_name);

	static void Clear();
};