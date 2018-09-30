#include "PieceManager.h"

const glm::vec2 Piece::operator[](const unsigned int p_iter) const
{
	if (p_iter >= amountPieces)
	{
		Error("There are not that many pieces!");
		std::cerr << __FUNCTION__ << " at " << __LINE__ << std::endl;
	}
	return position[p_iter];
}

const PieceName Piece::GetName() const
{
	return name;
}

const unsigned short Piece::AmountPieces() const
{
	return amountPieces;
}

const bool Piece::IsWhite() const
{
	return isWhite;
}

void PieceManager::RenderAll(SpriteRenderer* p_renderer)
{
	for (unsigned int iter = 0; iter < Pieces.size(); iter++)
	{
		for (unsigned int iter2 = 0; iter2 < Pieces[iter].AmountPieces(); iter2++)
			p_renderer->DrawSprite(TextureLoader::GetTexture(Pieces[iter].GetName()), Pieces[iter][iter2]);
	}
}