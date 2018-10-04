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

void InputManager::RightButtonClick(GLFWwindow* window, InputManager* inptMgr)
{
	double xpos;
	double ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	if (clickedOnPiece)
	{
		glm::vec2 convertedCoords = ConvertCursorCoords(window, xpos, ypos);
		if (convertedCoords.x < -0.8f || convertedCoords.y > 0.8f || convertedCoords.x > 0.8f || convertedCoords.y < -0.8f) return;   //what to return when invalid position
		glm::vec2 centreCoords = GetTileCentre(convertedCoords.x, convertedCoords.y);
//		for()
	}
}

glm::vec2 InputManager::ConvertCursorCoords(GLFWwindow* window, double xpos, double ypos)
{
	int windowx, windowy;
	glfwGetWindowSize(window, &windowx, &windowy);

	xpos -= windowx / 2;
	ypos -= windowy / 2;

	xpos /= (windowx / 2);
	ypos /= (windowy / 2) * -1;

	return glm::vec2(xpos, ypos);
}

std::string InputManager::GetTileName(GLFWwindow* window, double xpos, double ypos)
{
	glm::vec2 convertedCoords = ConvertCursorCoords(window, xpos, ypos);
	if (convertedCoords.x < -0.8f || convertedCoords.y > 0.8f || convertedCoords.x > 0.8f || convertedCoords.y < -0.8f) return "";   //what to return when invalid position
	glm::vec2 centreCoords = GetTileCentre(convertedCoords.x, convertedCoords.y);
	centreCoords.x += 0.8f;
	centreCoords.y += 0.8f;
	
	centreCoords.x /= 0.2f;
	centreCoords.y /= 0.2f;

	std::cout << "Mouse Position in GL coordinates   x: " << ConvertCursorCoords(window, xpos, ypos).x <<
		" | y: " << ConvertCursorCoords(window, xpos, ypos).y << std::endl;
	std::cout << "Tile Centres   x: " << centreCoords.x << " | y: " << centreCoords.y << std::endl;

	char ranks[8] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
	char files[8] = { '1', '2', '3', '4', '5', '6', '7', '8' };
	const char result[3] = { ranks[(int)centreCoords.x % 8], files[(int)centreCoords.y % 8], '\0' };
	return result;
}