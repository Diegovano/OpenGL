#pragma once
#include "../Chess Board/ChessBoard.h"
#include "../Sprite/Sprite Renderer/SpriteRenderer.h"
#include "../Sprite/Texture Loader/textureLoader.h"
#include <vector>

#ifdef _DEBUG
#define DBG_NEW new ( _CLIENT_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif


enum PieceName
{
	WK = 1,
	WQ = 2,
	WB = 3,
	WN = 4,
	WR = 5,
	WP = 6,
	BK = -1,
	BQ = -2,
	BB = -3,
	BN = -4,
	BR = -5,
	BP = -6,
};

class Piece //if unclear: refering to type of piece, not individual piece, one Piece obj for all pawns etc..
{
	PositionName position[8];
	PieceName name;
	bool isWhite;
	bool isMoved;
	unsigned short amountPieces;
public:
	Piece(PieceName p_name) : name(p_name), isWhite(name < 0 ? false : true), isMoved(false)
	{
		switch (abs(name))
		{
		case(WK):
			position[0] = e1; //All Kings because of abs(name), all queens etc...
			amountPieces = 1;
			break;
		case(WQ): 
			position[0] = d1;
			amountPieces = 1;
			break;
		case(WB):
			position[0] = c1;
			position[1] = f1;
			amountPieces = 2;
			break;
		case(WN):
			position[0] = b1;
			position[1] = g1;
			amountPieces = 2;
			break;
		case(WR):
			position[0] = a1;
			position[1] = h1;
			amountPieces = 2;
			break;
		case(WP):
			position[0] = a2;
			position[1] = b2;
			position[2] = c2;
			position[3] = d2;
			position[4] = e2;
			position[5] = f2;
			position[6] = g2;
			position[7] = h2;
			amountPieces = 8;
		}
		if (!isWhite) //For black pieces, move to the other side of the board
		{
			for (unsigned int iter = 0; iter < amountPieces; iter++)
			{
				if (abs(name) != WP) position[iter] = static_cast<PositionName>(position[iter] + 7);
				else position[iter] = static_cast<PositionName>(position[iter] + 5); //pawns are on different ranks
			}
		}
	}

	const PositionName operator[](const unsigned int p_iter) const;

	const PieceName GetName() const;
	const bool IsWhite() const;
	const unsigned short AmountPieces() const;
};

class PieceManager
{
	std::vector<Piece> Pieces;

public:
	PieceManager()
	{
		Pieces.push_back(Piece(WK));
		Pieces.push_back(Piece(WQ));
		Pieces.push_back(Piece(WB));
		Pieces.push_back(Piece(WN));
		Pieces.push_back(Piece(WR));
		Pieces.push_back(Piece(WP));

		Pieces.push_back(Piece(BK));
		Pieces.push_back(Piece(BQ));
		Pieces.push_back(Piece(BB));
		Pieces.push_back(Piece(BN));
		Pieces.push_back(Piece(BR));
		Pieces.push_back(Piece(BP));
	}

	void RenderAll(SpriteRenderer* p_renderer);
};