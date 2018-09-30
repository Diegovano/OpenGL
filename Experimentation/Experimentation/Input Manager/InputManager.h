#pragma once
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <iostream>

class InputManager
{
public:
	static void OnMBClick(GLFWwindow* window, int button, int action, int mods);

	GLFWmousebuttonfun GetMButtonCallback();
	glm::vec2 ConvertCursorCoords(GLFWwindow* window, double xpos, double ypos);
};