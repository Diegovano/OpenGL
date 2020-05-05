#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "Window/Window.h"
#include "ChessCore/chessCore.h"
#include "Input Manager/InputManager.h"

extern GLabs::ShaderProgram ShaderProgram();

int main(int argc, char* argv[])
{
	Window mainWindow("GLChess", 720, 720);
	mainWindow.WindowSetIcon("rsc\\icon.png", 64);

	InputManager inpt;
	mainWindow.SetUserPtr(&inpt);
	mainWindow.SetMouseButtonCallback(inpt.GetMButtonCallback());
	ChessGame game(&inpt);

	while (mainWindow.WindowOpen())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(91/255.0f, 54/255.0f, 36/255.0f, +1.0f);

		game.BoardRender();
		game.ChessRender();

		mainWindow.WindowUpdate();
	}
	mainWindow.WindowDestroy();
	return 0;
}