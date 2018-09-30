#pragma once
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

class InputManager
{
	void RightButtonClick(GLFWwindow* window, InputManager* inptMgr);
public:
	static void OnMBClick(GLFWwindow* window, int button, int action, int mods);

	GLFWmousebuttonfun GetMButtonCallback();
	glm::vec2 ConvertCursorCoords(GLFWwindow* window, double xpos, double ypos);
};