#pragma once
#include "../logger.h"
#include <GLEW/include/GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb-master/stb_image.h>

class Window
{
private:

	const char* m_name;
	unsigned int m_height, m_width;
	float m_aspectRatio;
	GLFWwindow* m_glfwWindow;
	
public: 

	explicit Window(const char* name, unsigned int width, unsigned int height) :
		m_name(name), m_height(height), m_width(width), m_aspectRatio(width / (float)height)
	{
		if (!glfwInit()) Error("GLFW Failed to Initialise!");
		WindowInit();
		OpenGLInit();
	}
	~Window(void)
	{

	}

public:

	void WindowInit(void);
	void OpenGLInit(void);
	void WindowSetIcon(const char* path, unsigned int size);
	const bool WindowOpen(void);
	void WindowUpdate(void);
	void WindowDestroy(void);
	void WindowGetSize(int &width, int &height);
	void SetCursorPosCallback(GLFWcursorposfun cbfun);
	void SetKeyCallback(GLFWkeyfun cbfun);

public: //getters

	const float WindowAspectRatio();
};