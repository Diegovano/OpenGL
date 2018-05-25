#pragma once

#include <GL/glew.h>
#include "entity_handler.h"

class Engine
{
public:
	Engine(void)
	{
		m_ehandler.ModelInit();
	}
	void Render(void)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	}
private:
	EntityHandler m_ehandler;
};