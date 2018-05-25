#include <iostream>
#include "window/init.h"
#include "window/window.h"
#include "engine/engine.h"

int main(int argc, char* argv[])
{
	GLFWInit();
	Window window("MYGAME", 1200, 750);
	window.WINInit();
	GLEWInit();

	Engine engine;

	while (window.WindowOpen())
	{
		engine.Render();
		window.UpdateDisplay();
	}

	window.DestroyWindow();

	std::cin.get();
}