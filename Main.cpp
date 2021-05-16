#include <Windows.h>
#include <crtdbg.h>
#include "PlayArea.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int show)
{
#ifdef _DEBUG
	_onexit(_CrtDumpMemoryLeaks);
#endif

	PlayArea window;
	window.create(hInstance, WINDOW_WIDTH, WINDOW_HEIGHT, 50, true);

	return 0;
}