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
	unsigned int m_moveNo;
	GLabs::ShaderProgram m_program, m_spriteProgram;
	SpriteRenderer *m_renderer;
	PieceManager m_pieces;
	BoardRenderer m_board;

public:
	ChessGame() : m_moveNo(0), m_program(ShaderProgram()), m_spriteProgram(SpriteShaderProgram()),
		m_renderer(new SpriteRenderer(m_spriteProgram)), m_board(BoardRenderer(m_program))
	{
		GetSprites();
	}

	void BoardRender();
	void ChessInitialise();
	void GetSprites();
	void ChessRender();
};