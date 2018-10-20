#include "InputManager.h"

void InputManager::OnMBClick(GLFWwindow* window, int button, int action, int mods)
{
	InputManager* inptMgr = (InputManager*)glfwGetWindowUserPointer(window);
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) inptMgr->RightButtonClick(window, inptMgr);
}

GLFWmousebuttonfun InputManager::GetMButtonCallback()
{
	return OnMBClick;
}

void InputManager::SpecifyPieceManager(PieceManager* mgrPtr)
{
	m_pieceManager = mgrPtr;
}

void InputManager::RightButtonClick(GLFWwindow* window, InputManager* inptMgr)
{
	double xpos;
	double ypos;
	glfwGetCursorPos(window, &xpos, &ypos);


	std::cout << xpos << ' ' << ypos << std::endl;
	glm::vec2 convertedCoords = ConvertCursorCoords(window, xpos, ypos);
	if (convertedCoords.x < -0.8f || convertedCoords.y > 0.8f || convertedCoords.x > 0.8f || convertedCoords.y < -0.8f) return;
	std::cout << convertedCoords.x << ' ' << convertedCoords.y << std::endl;
	std::cout << GetTileName(window, convertedCoords.x, convertedCoords.y) << std::endl;


	if (!clickedOnPiece)
	{
		glm::vec2 centreCoords = GetTileCentre(convertedCoords.x, convertedCoords.y);
		std::cout << GetTileName(window, centreCoords.x, centreCoords.y) << std::endl;
		std::cout << "Tile Centres   x: " << centreCoords.x << " | y: " << centreCoords.y << std::endl;
//		std::cin.get();
		for (unsigned int iter = 0; iter < m_pieceManager->Pieces.size(); iter++)
		{
			for (unsigned int iter2 = 0; iter2 < m_pieceManager->Pieces[iter].AmountPieces(); iter2++)
			{
				if (*m_pieceManager->Pieces[iter][iter2] == centreCoords)
				{
					m_ptrToLastClickedPiece =
						m_pieceManager->Pieces[iter][iter2];
					clickedOnPiece = true;
					return;
				}
			}
		}
	}
	else
	{
		if (convertedCoords.x < -0.8f || convertedCoords.y > 0.8f || convertedCoords.x > 0.8f || convertedCoords.y < -0.8f) return;   //what to return when invalid position
		glm::vec2 centreCoords = GetTileCentre(convertedCoords.x, convertedCoords.y);
		*m_ptrToLastClickedPiece = centreCoords;
		clickedOnPiece = false;
		std::cout << m_pieceManager->Pieces[4][0]->x << ' ' << m_pieceManager->Pieces[4][0]->y << std::endl;
	} 
}

glm::vec2 InputManager::ConvertCursorCoords(GLFWwindow* window, double xpos, double ypos)
{
	int windowx, windowy;				//look into how glfw positions work?
	glfwGetWindowSize(window, &windowx, &windowy);

	xpos -= windowx / 2;
	ypos -= windowy / 2;

	xpos /= (windowx / 2);
	ypos /= (windowy / 2) * -1;

	return glm::vec2(xpos, ypos);
}

std::string InputManager::GetTileName(GLFWwindow* window, double converted_x, double converted_y)
{
	glm::vec2 centreCoords = GetTileCentre(converted_x, converted_y);
	std::cout << "Mouse Position in GL coordinates   x: " << converted_x <<
		" | y: " << converted_y << std::endl;
	std::cout << "Tile Centre   x: " << centreCoords.x << " | y: " << centreCoords.y << std::endl;

	centreCoords.x += 0.8f;
	centreCoords.y += 0.8f;

	centreCoords.x /= 0.2f;
	centreCoords.y /= 0.2f;

	char ranks[8] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
	char files[8] = { '1', '2', '3', '4', '5', '6', '7', '8' };
	const char result[3] = { ranks[(int)centreCoords.x % 8], files[(int)centreCoords.y % 8], '\0' };
	return result;
}