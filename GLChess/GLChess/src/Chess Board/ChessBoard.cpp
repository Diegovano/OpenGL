#include "ChessBoard.h"

glm::vec2 ChessBoard::GetPosition(PositionNames p_position)
{
	glm::vec2 worldSpaceCoord(-0.9f, -0.9f);
	
	unsigned int xPos, yPos;
	yPos = p_position / 10;
	xPos = p_position - yPos * 10;

	worldSpaceCoord.x += xPos * 0.2f;
	worldSpaceCoord.y += yPos * 0.2f;

	return worldSpaceCoord;
}