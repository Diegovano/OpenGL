#include "window.h"

Window::Window(const char* title, int32_t width, int32_t height)
	: m_title(title), m_width(width), m_height(height)
{
}

void Window::WINInit(void) 
{
	m_window = glfwCreateWindow(m_width, m_height, m_title, 0, 0);
	if (!m_window)
	{
		std::cerr << "error initializing window\n";
		glfwTerminate();
	}
	glfwMakeContextCurrent(m_window);
}

bool Window::WindowOpen(void) const
{
	return !glfwWindowShouldClose(m_window);
}

void Window::UpdateDisplay(void) const
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void Window::DestroyWindow(void)
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}