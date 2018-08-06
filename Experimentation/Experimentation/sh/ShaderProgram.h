#pragma once
#include <fstream>
#include <GLEW/include/GL/glew.h>
#include "../Abstraction/GLabs.h"

GLuint ShaderProgram()
{
	std::ifstream vshFileStream("D:\\Program Files (x86)\\msdev\\OpenGL\\Experimentation\\Experimentation\\sh\\vsh.shader");
	std::ifstream fshFileStream("D:\\Program Files (x86)\\msdev\\OpenGL\\Experimentation\\Experimentation\\sh\\fsh.shader");

	std::string vertexShaderStr = std::string(std::istreambuf_iterator<char>(vshFileStream), std::istreambuf_iterator<char>());
	std::string fragmentShaderStr = std::string(std::istreambuf_iterator<char>(fshFileStream), std::istreambuf_iterator<char>());

	const char* vertexShaderCStr[1] = { vertexShaderStr.c_str() };
	const char* fragmentShaderCStr[1] = { fragmentShaderStr.c_str() };

	GLabs::Shader vertexShader(GL_VERTEX_SHADER), fragmentShader(GL_FRAGMENT_SHADER);

	vertexShader.AttachSource(vertexShaderCStr);
	fragmentShader.AttachSource(fragmentShaderCStr);

	vertexShader.Compile();
	fragmentShader.Compile();

	GLabs::ShaderProgram shaderProgram;

	shaderProgram.AttachShader(vertexShader);
	shaderProgram.AttachShader(fragmentShader);

	shaderProgram.Link();

	shaderProgram.UseProgram();

	vertexShader.Delete();
	fragmentShader.Delete();

	return shaderProgram.ProgramID();
}