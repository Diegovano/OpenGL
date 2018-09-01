#pragma once
#include "../Geometry/GeometryGenerator.h"
#include "../Abstraction/GLabs.h"
#include "../Sprite/Sprite Renderer/SpriteRenderer.h"
#include "../Sprite/Texture Loader/textureLoader.h"
#include "../Chess Board/ChessBoard.h"
#include "../Piece Manager/PieceManager.h"
#include "../Board Renderer/BoardRenderer.h"

extern GLabs::ShaderProgram ShaderProgram();
extern GLabs::ShaderProgram SpriteShaderProgram();

class ChessGame
{
	unsigned int moveNo;
	GLabs::ShaderProgram m_program, m_spriteProgram;
	SpriteRenderer *m_renderer;
	PieceManager m_pieces;
	BoardRenderer m_board;
public:
	ChessGame() : moveNo(0), m_program(ShaderProgram()), m_spriteProgram(SpriteShaderProgram()), m_renderer(new SpriteRenderer(m_spriteProgram)),
		m_board(BoardRenderer::BoardRenderer(m_program))
	{
		GetSprites();
	}

	void BoardRender();
	void GetSprites();
	void ChessRender();
};