#pragma once
#include <vector>
#include "../logger.h"
#include "BufferData.h"
#include <GLEW/include/GL/glew.h>

class RenderManager
{
	std::vector<BufferData> BufferList;
public:
	void DrawAllBuffers();
	void DrawBuffer(GLuint p_bufferToRender);

	void AddBuffer(BufferData p_bufferID);
};