#include "BoardRenderer.h"

void BoardRenderer::BoardAlloc(GLabs::ShaderProgram program)
{
	program.UseProgram();

	GeometryData blackSquare = GeometryGenerator::GetSquare();
	GeometryData bigSquare = GeometryGenerator::GetWhiteSquareBack();

	m_bigSquareBuffer.Reserve(GL_ELEMENT_ARRAY_BUFFER, bigSquare.TotalBufferSize(), GL_STATIC_DRAW);
	m_bigSquareBuffer.SubData(GL_ARRAY_BUFFER, 0, bigSquare.VertexBufferSize(), bigSquare.vertices);
	m_bigSquareBuffer.SubData(GL_ELEMENT_ARRAY_BUFFER, bigSquare.VertexBufferSize(), bigSquare.IndexBufferSize(), bigSquare.indices);

	m_blackSquaresBuffer.Reserve(GL_ELEMENT_ARRAY_BUFFER, blackSquare.TotalBufferSize(), GL_STATIC_DRAW);
	m_blackSquaresBuffer.SubData(GL_ARRAY_BUFFER, 0, blackSquare.VertexBufferSize(), blackSquare.vertices);
	m_blackSquaresBuffer.SubData(GL_ELEMENT_ARRAY_BUFFER, blackSquare.VertexBufferSize(), blackSquare.IndexBufferSize(), blackSquare.indices);
	
	GLfloat xOffsets[] = { 0.0f, 0.4f, 0.8f, 1.2f, 0.2f, 0.6f, 1.0f, 1.4f, 0.0f, 0.4f, 0.8f, 1.2f, 0.2f, 0.6f, 1.0f, 1.4f,
		0.0f, 0.4f, 0.8f, 1.2f, 0.2f, 0.6f, 1.0f, 1.4f, 0.0f, 0.4f, 0.8f, 1.2f, 0.2f, 0.6f, 1.0f, 1.4f };
	GLfloat yOffsets[] = { 0.0f, 0.2f, 0.4f, 0.6f, 0.8f, 1.0f, 1.2f, 1.4f };

	m_offsetsBuffer.Reserve(GL_ARRAY_BUFFER, sizeof(xOffsets) + sizeof(yOffsets), GL_STATIC_DRAW);
	m_offsetsBuffer.SubData(GL_ARRAY_BUFFER, 0, sizeof(xOffsets), xOffsets);
	m_offsetsBuffer.SubData(GL_ARRAY_BUFFER, sizeof(xOffsets), sizeof(yOffsets), yOffsets);

	m_bigSquareVertexSize = bigSquare.VertexBufferSize();
	m_bigSquareIndexSize = bigSquare.IndexBufferSize();
	m_blackSquareVertexSize = blackSquare.VertexBufferSize();
	m_blackSquareIndexSize = blackSquare.IndexBufferSize();

	bigSquare.CleanUp();
	blackSquare.CleanUp();
}

void BoardRenderer::BoardRender()
{
/*	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*)m_bigSquareVertexSize);

	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, nullptr);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, (void*)(32 * sizeof(float)));
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 4);

	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*)m_blackSquareVertexSize, 32); 

	GeometryData debugSquare = GeometryGenerator::GetSquare(); 

	GLabs::Buffer tempBuffer;
	tempBuffer.Reserve(GL_ELEMENT_ARRAY_BUFFER, debugSquare.TotalBufferSize(), GL_STATIC_DRAW);
	tempBuffer.SubData(GL_ELEMENT_ARRAY_BUFFER, 0, debugSquare.VertexBufferSize(), debugSquare.vertices);
	tempBuffer.SubData(GL_ARRAY_BUFFER, debugSquare.VertexBufferSize(), debugSquare.IndexBufferSize(), debugSquare.indices);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glDrawElements(GL_TRIANGLES, debugSquare.numIndices, GL_UNSIGNED_SHORT, debugSquare.indices);
	debugSquare.CleanUp(); */

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

}