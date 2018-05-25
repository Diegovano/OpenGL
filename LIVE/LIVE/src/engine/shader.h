#pragma once

#include <iostream>
#include <GL/glew.h>
#include <fstream>

class Shader
{
public:
	Shader(void) = default;
	Shader(GLenum shadertype, const std::string& dir)
	{
	}
private:
	std::string ExtractShaderSource(const std::string& dir)
	{
		std::ifstream file(dir);
		if (!file)
		{
			std::cerr << "couldn't locate " << dir << std::endl;
		}
		return std::string(std::istreambuf_iterator<char>(file),
			std::istreambuf_iterator<char>());
	}
private:
	uint32_t m_shaderID;
};