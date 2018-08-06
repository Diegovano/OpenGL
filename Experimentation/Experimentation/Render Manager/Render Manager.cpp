#include "Render Manager.h"

void RenderManager::DrawAllBuffers()
{
	for (unsigned int iter = 0; iter < BufferList.size(); iter++)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferList.at(iter).bufferID);
		glDrawElements(GL_TRIANGLES, BufferList.at(iter).quantIndices, GL_UNSIGNED_SHORT, 0);//change 0
	}
}
void RenderManager::DrawBuffer(GLuint p_bufferToRender)
{
	int BufferLocation = -1;
	for (unsigned int iter = 0; iter < BufferList.size(); iter++)
	{
		if (BufferList.at(iter).bufferID == p_bufferToRender)BufferLocation = iter;
	}
	if (BufferLocation == -1)
	{
		Error("The following buffer goesn't exist: Cannot Render!");
		Error(p_bufferToRender);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferList.at(BufferLocation).bufferID);
	glDrawElements(GL_TRIANGLES, BufferList.at(BufferLocation).quantIndices, GL_UNSIGNED_SHORT, 0); //change 0
}

void RenderManager::AddBuffer(BufferData p_bufferID)
{
	BufferList.push_back(p_bufferID);
}