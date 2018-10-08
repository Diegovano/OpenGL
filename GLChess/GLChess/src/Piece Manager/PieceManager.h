#pragma once
#include "../Chess Board/ChessBoard.h"
#include "../Sprite/Sprite Renderer/SpriteRenderer.h"
#include "../Sprite/Texture Loader/textureLoader.h"
#include <vector>

extern glm::vec2** Board;

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

enum Direction
{
	UP = 1,
	DN = -1,
	RT = 10,
	LF = -10
};

class Piece //if unclear: refering to type of piece, not individual piece, one Piece obj for all pawns etc..
{
	glm::vec2* position;
	PieceName name;
	bool isWhite;
	bool isMoved;
	unsigned short amountPieces;
public:
	Piece(PieceName p_name) : name(p_name), isWhite(name < 0 ? false : true), isMoved(false)
	{
		switch (abs(name)) //All Kings because of abs(name), all queens etc...
		{
		case(WK): position = new glm::vec2[1];
			if (name == WK) position[0] = Board[4][0];
			else position[0] = Board[4][7]; 
			amountPieces = 1;
			break;
		case(WQ): position = new glm::vec2[1];
			if (name == WQ) position[0] = Board[3][0];
			else position[0] = Board[3][7];
			amountPieces = 1;
			break;
		case(WB): position = new glm::vec2[2];
			if (name == WB)
			{
				position[0] = Board[2][0];
				position[1] = Board[5][0];
			}
			else
			{
				position[0] = Board[2][7];
				position[1] = Board[5][7];
			}
			amountPieces = 2;
			break;
		case(WN): position = new glm::vec2[2];
			if (name == WN)
			{
				position[0] = Board[1][0];
				position[1] = Board[6][0];
			}
			else
			{
				position[0] = Board[1][7];
				position[1] = Board[6][7];
			}
			amountPieces = 2;
			break;
		case(WR): position = new glm::vec2[2];
			if (name == WR)
			{
				position[0] = Board[0][0];
				position[1] = Board[7][0];
			}
			else
			{
				position[0] = Board[0][7];
				position[1] = Board[7][7];
			}
			amountPieces = 2;
			break;
		case(WP): position = new glm::vec2[8];
			if (name == WP)
			{
				position[0] = Board[0][1];
				position[1] = Board[1][1];
				position[2] = Board[2][1];
				position[3] = Board[3][1];
				position[4] = Board[4][1];
				position[5] = Board[5][1];
				position[6] = Board[6][1];
				position[7] = Board[7][1];
			}
			else
			{
				position[0] = Board[0][6];
				position[1] = Board[1][6];
				position[2] = Board[2][6];
				position[3] = Board[3][6];
				position[4] = Board[4][6];
				position[5] = Board[5][6];
				position[6] = Board[6][6];
				position[7] = Board[7][6];
			}
			amountPieces = 8; 
		}
	}

	glm::vec2 operator[](const unsigned int p_iter) const;

	const PieceName GetName() const;
	const bool IsWhite() const;
	const unsigned short AmountPieces() const;
};

class PieceManager
{
public:
	std::vector<Piece> Pieces;

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