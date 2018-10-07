#pragma once
#include <iostream>
#include "../Piece Manager/PieceManager.h"
#include <GLFW/glfw3.h>
#include <string>

class InputManager
{
	bool clickedOnPiece = false;
	void RightButtonClick(GLFWwindow* window, InputManager* inptMgr);
	PieceManager* m_pieceManager;

	glm::vec2* m_ptrToLastClickedPiece;

public:

	static void OnMBClick(GLFWwindow* window, int button, int action, int mods);

	GLFWmousebuttonfun GetMButtonCallback();
	void SpecifyPieceManager(PieceManager* mgrPtr);
	glm::vec2 ConvertCursorCoords(GLFWwindow* window, double xpos, double ypos);
	std::string GetTileName(GLFWwindow* window, double xpos, double ypos);
};