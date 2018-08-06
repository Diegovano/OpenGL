#define STB_IMAGE_IMPLEMENTATION
#include "Window.h"

void Window::WindowInit(void)
{
	m_glfwWindow = glfwCreateWindow(m_width, m_height, m_name, 0, 0);
	glfwMakeContextCurrent(m_glfwWindow);
	if (!m_glfwWindow)
	{
		Error("GLFW Window did not initialise!");
		glfwTerminate();
		exit(1);
	}
	Log("GLFW initialised.");
	glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::OpenGLInit(void)
{
	GLenum errCode = glewInit();
	if (errCode != GLEW_OK)
	{
		Error("GLEW could not initialise");
		glfwTerminate();
		exit(1);
	}
	Log("GLEW initialised.");
	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CULL_FACE);
}

void Window::WindowSetIcon(const char* path, unsigned int size)
{
	GLFWimage images[1];
	images[0].height = size;
	images[0].width = size;
	images[0].pixels = stbi_load(path, &images[0].height, &images[0].width, 0, 4);
	glfwSetWindowIcon(m_glfwWindow, 1, images);
	stbi_image_free(images[0].pixels);
}

const bool Window::WindowOpen()
{
	if (!glfwWindowShouldClose(m_glfwWindow)
		&& !(glfwGetKey(m_glfwWindow, GLFW_KEY_ESCAPE)))
		return true;
	else return false;
}

void Window::WindowUpdate(void)
{
	glfwSwapBuffers(m_glfwWindow);
	glfwPollEvents();
}

void Window::WindowDestroy(void)
{
	glfwDestroyWindow(m_glfwWindow);
}

void Window::WindowGetSize(int &width, int &height)
{
	glfwGetWindowSize(m_glfwWindow, &width, &height);
}

void Window::SetCursorPosCallback(GLFWcursorposfun cbfun)
{
	glfwSetCursorPosCallback(m_glfwWindow, cbfun);
}

void Window::SetKeyCallback(GLFWkeyfun cbfun)
{
	glfwSetKeyCallback(m_glfwWindow, cbfun);
}

const float Window::WindowAspectRatio()
{
	return m_aspectRatio;
}