#include "chessCore.h"


void ChessGame::BoardRender()
{
	GeometryData bSquare = GeometryGenerator::GetSquare();
	GeometryData bigSquare = GeometryGenerator::GetWhiteSquareBack();

	GLabs::Buffer whiteSquareBuffer;
	whiteSquareBuffer.Reserve(GL_ELEMENT_ARRAY_BUFFER, bigSquare.TotalBufferSize(), GL_STATIC_DRAW);
	whiteSquareBuffer.SubData(GL_ARRAY_BUFFER, 0, bigSquare.VertexBufferSize(), bigSquare.vertices);
	whiteSquareBuffer.SubData(GL_ELEMENT_ARRAY_BUFFER, bigSquare.VertexBufferSize(), bigSquare.IndexBufferSize(), bigSquare.indices);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glDrawElements(GL_TRIANGLES, bigSquare.numIndices, GL_UNSIGNED_SHORT, (void*)bigSquare.VertexBufferSize());

	GLabs::Buffer blackSquareBuffer;
	blackSquareBuffer.Reserve(GL_ARRAY_BUFFER, bSquare.TotalBufferSize(), GL_STATIC_DRAW);
	blackSquareBuffer.SubData(GL_ARRAY_BUFFER, 0, bSquare.VertexBufferSize(), bSquare.vertices);
	blackSquareBuffer.SubData(GL_ELEMENT_ARRAY_BUFFER, bSquare.VertexBufferSize(), bSquare.IndexBufferSize(), bSquare.indices);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));

	GLfloat xOffsets[] = { 0.0f, 0.4f, 0.8f, 1.2f, 0.2f, 0.6f, 1.0f, 1.4f, 0.0f, 0.4f, 0.8f, 1.2f, 0.2f, 0.6f, 1.0f, 1.4f,
		0.0f, 0.4f, 0.8f, 1.2f, 0.2f, 0.6f, 1.0f, 1.4f, 0.0f, 0.4f, 0.8f, 1.2f, 0.2f, 0.6f, 1.0f, 1.4f };
	GLfloat yOffsets[] = { 0.0f, 0.2f, 0.4f, 0.6f, 0.8f, 1.0f, 1.2f, 1.4f };

	GLabs::Buffer offsetsBuffer;
	offsetsBuffer.Reserve(GL_ARRAY_BUFFER, sizeof(xOffsets) + sizeof(yOffsets), GL_STATIC_DRAW);
	offsetsBuffer.SubData(GL_ARRAY_BUFFER, 0, sizeof(xOffsets), xOffsets);
	offsetsBuffer.SubData(GL_ARRAY_BUFFER, sizeof(xOffsets), sizeof(yOffsets), yOffsets);

	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, nullptr);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(xOffsets)));
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 4);

	glDrawElementsInstanced(GL_TRIANGLES, bSquare.numIndices, GL_UNSIGNED_SHORT, (void*)bSquare.VertexBufferSize(), 32);

	bSquare.CleanUp();
}

void ChessGame::ChessInitialise()
{

}

void ChessGame::ChessRender()
{

	GeometryData* pieces;
}