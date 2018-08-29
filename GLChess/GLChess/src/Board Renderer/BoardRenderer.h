#pragma once
#include "../Geometry/GeometryGenerator.h"
#include "../Abstraction/GLabs.h"

class BoardRenderer
{
	GLabs::Buffer m_bigSquareBuffer, m_blackSquaresBuffer, m_offsetsBuffer;

	GLsizeiptr m_bigSquareVertexSize, m_bigSquareIndexSize, m_blackSquareVertexSize,
		m_blackSquareIndexSize;

	void BoardAlloc(GLabs::ShaderProgram program);
public:
	BoardRenderer(GLabs::ShaderProgram program)
	{
		BoardAlloc(program);
	}

	void BoardRender();
};