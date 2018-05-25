#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(void) = default;
	Window(const Window&) = delete;
	const Window& operator=(const Window&) = delete;

	Window(const char* title, int32_t width, int32_t height);
	void WINInit(void);

	bool WindowOpen(void) const;
	void UpdateDisplay(void) const;

	void DestroyWindow(void);
private:
	GLFWwindow* m_window;
	int32_t m_width;
	int32_t m_height;
	const char* m_title;
};