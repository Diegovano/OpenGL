#pragma once
#include "GeometryData.h"

struct GeometryGenerator
{
	//board
	static GeometryData GetWhiteSquareBack();
	static GeometryData GetSquare();
	static GeometryData GetOutline();

	//pieces
	static GeometryData GetKing(bool isWhite);
	static GeometryData GetQueen(bool isWhite);
	static GeometryData GetKnight(bool isWhite);
	static GeometryData GetBishop(bool isWhite);
	static GeometryData GetRook(bool isWhite);
	static GeometryData GetPawn(bool isWhite);
};