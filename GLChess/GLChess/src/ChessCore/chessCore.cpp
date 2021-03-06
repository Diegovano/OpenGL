#include "chessCore.h"

void ChessGame::BoardRender()
{
	m_board.BoardRender();
}

void ChessGame::GetSprites()
{
	m_spriteProgram.UseProgram();

	TextureLoader::LoadTexture("..\\GLChess\\rsc\\Sprites\\wk.png", GL_TRUE, WK);
	TextureLoader::LoadTexture("..\\GLChess\\rsc\\Sprites\\wq.png", GL_TRUE, WQ);
	TextureLoader::LoadTexture("..\\GLChess\\rsc\\Sprites\\wb.png", GL_TRUE, WB);
	TextureLoader::LoadTexture("..\\GLChess\\rsc\\Sprites\\wn.png", GL_TRUE, WN);
	TextureLoader::LoadTexture("..\\GLChess\\rsc\\Sprites\\wr.png", GL_TRUE, WR);
	TextureLoader::LoadTexture("..\\GLChess\\rsc\\Sprites\\wp.png", GL_TRUE, WP);

	TextureLoader::LoadTexture("..\\GLChess\\rsc\\Sprites\\bk.png", GL_TRUE, BK);
	TextureLoader::LoadTexture("..\\GLChess\\rsc\\Sprites\\bq.png", GL_TRUE, BQ);
	TextureLoader::LoadTexture("..\\GLChess\\rsc\\Sprites\\bb.png", GL_TRUE, BB);
	TextureLoader::LoadTexture("..\\GLChess\\rsc\\Sprites\\bn.png", GL_TRUE, BN);
	TextureLoader::LoadTexture("..\\GLChess\\rsc\\Sprites\\br.png", GL_TRUE, BR);
	TextureLoader::LoadTexture("..\\GLChess\\rsc\\Sprites\\bp.png", GL_TRUE, BP);
}

void ChessGame::ChessRender()
{
	m_pieces.RenderAll(m_renderer);
}

/*InputManager* ChessGame::operator=(ChessGame game)
{
	return &m_inputManager;
}*/