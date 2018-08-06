#pragma once
#include "../Geometry/GeometryGenerator.h"
#include "../Abstraction/GLabs.h"

class ChessGame
{
	unsigned int moveNo;
public:
	ChessGame() : moveNo(0)
	{

	}

	static void BoardRender();

	void ChessInitialise();
	void ChessRender();
};