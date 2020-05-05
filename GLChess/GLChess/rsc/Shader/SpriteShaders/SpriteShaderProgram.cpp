#include <fstream>
#include <GLEW/include/GL/glew.h>
#include "../GLChess/src/Abstraction/GLabs.h"

GLabs::ShaderProgram SpriteShaderProgram()
{
	std::ifstream vshFileStream("..\\GLChess\\rsc\\Shader\\SpriteShaders\\spriteVsh.shader");
	std::ifstream fshFileStream("..\\GLChess\\rsc\\Shader\\SpriteShaders\\spriteFsh.shader");

	std::string strVertexShader = std::string(std::istreambuf_iterator<char>(vshFileStream), std::istreambuf_iterator<char>());
	std::string strFragmentShader = std::string(std::istreambuf_iterator<char>(fshFileStream), std::istreambuf_iterator<char>());

	const char* vshCStr[1] = { strVertexShader.c_str() };
	const char* fshCStr[1] = { strFragmentShader.c_str() };

	GLabs::Shader VertexShader(GL_VERTEX_SHADER), FragmentShader(GL_FRAGMENT_SHADER);

	VertexShader.AttachSource(vshCStr);
	FragmentShader.AttachSource(fshCStr);

	VertexShader.Compile();
	FragmentShader.Compile();

	GLabs::ShaderProgram SpriteShaderProgram;

	SpriteShaderProgram.AttachShader(VertexShader);
	SpriteShaderProgram.AttachShader(FragmentShader);

	SpriteShaderProgram.Link();

	VertexShader.Delete();
	FragmentShader.Delete();

	return SpriteShaderProgram;
}