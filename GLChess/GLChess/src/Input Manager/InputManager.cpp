#include "InputManager.h"
#include <iostream>

void InputManager::OnMBClick(GLFWwindow* window, int button, int action, int mods)
{
	InputManager* inptMgr = (InputManager*)glfwGetWindowUserPointer(window);
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) inptMgr->RightButtonClick(window, inptMgr);
}

GLFWmousebuttonfun InputManager::GetMButtonCallback()
{
	return OnMBClick;
}

void InputManager::RightButtonClick(GLFWwindow* window, InputManager* inptMgr)
{
	double xpos;
	double ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	std::cout << inptMgr->ConvertCursorCoords(window, xpos, ypos).x << ' ' << inptMgr->ConvertCursorCoords(window, xpos, ypos).y << std::endl;
}

glm::vec2 InputManager::ConvertCursorCoords(GLFWwindow* window, double xpos, double ypos)
{
	int windowx, windowy;
	glfwGetWindowSize(window, &windowx, &windowy);

	xpos -= windowx / 2;
	ypos -= windowy / 2;

	xpos /= (windowx / 2);
	ypos /= (windowy / 2);

	return glm::vec2(xpos, ypos);
}