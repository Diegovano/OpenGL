#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>  
#include <crtdbg.h>  
#ifdef _DEBUG
#define DBG_NEW new ( _CLIENT_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif
#include "Window/Window.h"
#include "ChessCore/chessCore.h"

extern GLabs::ShaderProgram ShaderProgram();

int main(int argc, char* argv[])
{
	Window mainWindow("GLChess", 720, 720);
	mainWindow.WindowSetIcon("rsc\\icon.png", 64);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ChessGame game;

	while (mainWindow.WindowOpen())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(91/255.0f, 54/255.0f, 36/255.0f, +1.0f);

		game.ChessRender();

		mainWindow.WindowUpdate();
	}
	_CrtDumpMemoryLeaks();
	mainWindow.WindowDestroy();
	return 0;
}