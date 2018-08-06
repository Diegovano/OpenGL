#pragma once
#include <GLEW/include/GL/glew.h>

struct BufferData
{
	GLuint bufferID;
	GLuint quantIndices;

	BufferData(GLuint p_bufferID, GLuint p_quantIndices) :
		bufferID(p_bufferID), quantIndices(p_quantIndices)
	{

	}
};