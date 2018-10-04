#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "glm/glm.hpp"
#include "../Chess Board/ChessBoard.h"

class InputManager
{
	bool clickedOnPiece = false;
	void RightButtonClick(GLFWwindow* window, InputManager* inptMgr);
public:
	static void OnMBClick(GLFWwindow* window, int button, int action, int mods);

	GLFWmousebuttonfun GetMButtonCallback();
	glm::vec2 ConvertCursorCoords(GLFWwindow* window, double xpos, double ypos);
	std::string GetTileName(GLFWwindow* window, double xpos, double ypos);
};