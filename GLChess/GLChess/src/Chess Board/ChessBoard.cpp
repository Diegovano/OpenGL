#include "ChessBoard.h"

glm::vec2 ChessBoard::GetPosition(PositionName p_position)
{
	glm::vec2 worldSpaceCoord(-0.9009f, -0.9f); //pieces seemed a bit off centred
	
	unsigned int xPos, yPos;
	xPos = p_position / 10;
	yPos = p_position - xPos * 10;

	worldSpaceCoord.x += xPos * 0.2f;
	worldSpaceCoord.y += yPos * 0.2f;

	return worldSpaceCoord;
}