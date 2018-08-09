#pragma once
#include "../Geometry/GeometryGenerator.h"
#include "../Abstraction/GLabs.h"
#include "../Sprite/Sprite Renderer/SpriteRenderer.h"
#include "../Sprite/Texture Loader/textureLoader.h"
#include "../Chess Board/ChessBoard.h"

extern GLabs::ShaderProgram ShaderProgram();
extern GLabs::ShaderProgram SpriteShaderProgram();

class ChessGame
{
	unsigned int moveNo;
	GLabs::ShaderProgram m_program, m_spriteProgram;
	SpriteRenderer *renderer;
public:
	ChessGame() : moveNo(0), m_program(ShaderProgram()), m_spriteProgram(SpriteShaderProgram())
	{
		GetSprites();
	}

	void BoardRender();

	void ChessInitialise();
	void GetSprites();
	void ChessRender();
};