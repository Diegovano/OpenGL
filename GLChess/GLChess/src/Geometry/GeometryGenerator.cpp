#include "GeometryGenerator.h"
#include <glm/glm.hpp>

GeometryData GeometryGenerator::GetWhiteSquareBack()
{
	GeometryData ret;

	glm::vec3 squareColour = glm::vec3(+235.0f, +199.0f, +164.0f);
	squareColour /= 255;

	Vertex bigSquare[]
	{
		glm::vec3(-0.8f, -0.8f, 0.5f),
		squareColour,

		glm::vec3(0.8f, -0.8f, 0.5f),
		squareColour,

		glm::vec3(0.8f, 0.8f, 0.5f),
		squareColour,

		glm::vec3(-0.8f, 0.8f, 0.5f),
		squareColour
	};

	ret.numVertices = sizeof(bigSquare) / sizeof(*bigSquare);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, bigSquare, sizeof(bigSquare));

	GLushort indices[]
	{
		0, 1, 2,
		2, 3, 0
	};

	ret.numIndices = sizeof(indices) / sizeof(*indices);
	ret.indices = new GLushort[ret.numIndices];
	memcpy(ret.indices, indices, sizeof(indices));

	return ret;
}

GeometryData GeometryGenerator::GetSquare()
{
	GeometryData ret;
	glm::vec3 squareColour = glm::vec3(+152.0f, +103.0f, 68.0f);
	squareColour /= 255;

	Vertex square[]
	{
		glm::vec3(-0.8f, -0.6f, +0.0f),
		squareColour,

		glm::vec3(-0.6f, -0.6f, +0.0f),
		squareColour,

		glm::vec3(-0.6f, -0.8f, +0.0f),
		squareColour,

		glm::vec3(-0.8f, -0.8f, +0.0f),
		squareColour
	};

	ret.numVertices = sizeof(square) / sizeof(*square);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, square, sizeof(square));

	GLushort indices[]
	{
		0, 1, 2, 
		3, 0, 2
	};
	
	ret.numIndices = sizeof(indices) / sizeof(*indices);
	ret.indices = new GLushort[ret.numIndices];
	memcpy(ret.indices, indices, sizeof(indices));

	return ret;
}
GeometryData GeometryGenerator::GetOutline()
{
	GeometryData ret;
	
	return ret;
}


GeometryData GeometryGenerator::GetKing(bool isWhite)
{			
	GeometryData ret;

	return ret;
}			
GeometryData GeometryGenerator::GetQueen(bool isWhite)
{	
	GeometryData ret;

	return ret;
}	
GeometryData GeometryGenerator::GetKnight(bool isWhite)
{		
	GeometryData ret;

	return ret;
}		
GeometryData GeometryGenerator::GetBishop(bool isWhite)
{			
	GeometryData ret;

	return ret;
}			
GeometryData GeometryGenerator::GetRook(bool isWhite)
{			
	GeometryData ret;

	return ret;
}			
GeometryData GeometryGenerator::GetPawn(bool isWhite)
{
	GeometryData ret;

	return ret;
}