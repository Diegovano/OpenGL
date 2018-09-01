#pragma once
#include "../Abstraction/GLabs.h"
#include "../Geometry/GeometryGenerator.h"

class BoardRenderer
{
	GLabs::Buffer m_whiteSquareBuffer, m_blackSquareBuffer, m_offsetsBuffer;
	GLabs::ShaderProgram m_program;
	

public:
	BoardRenderer(GLabs::ShaderProgram program) : m_program(program)
	{

	}

	void BoardRender();
};