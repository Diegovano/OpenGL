#include "ChessBoard.h"

glm::vec2** AssignBoardCoords()
{
	glm::vec2** board = new glm::vec2*[8];
	for (unsigned int index = 0; index < 8; index++)
	{
		board[index] = new glm::vec2[8];
	}
	for (unsigned int index = 0; index < 8; index++)
	{
		for (unsigned int index2 = 0; index2 < 8; index2++)
		{
			board[index][index2] = glm::vec2(-0.7f + 0.2f * index, -0.7f + 0.2f * index2);
		}
	}
	return board;
}

glm::vec2 GetMovement(int x, int y)
{
	return glm::vec2(x*0.2f, y*0.2f);
}
 
glm::vec2 GetTileCentre(double x, double y)
{
	unsigned int xtile = (x + 0.8f) / 0.2f;
	unsigned int ytile = (y + 0.8f) / 0.2f;

	return Board[xtile][ytile];
}

glm::vec2** Board(AssignBoardCoords());