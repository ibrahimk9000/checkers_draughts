#include "game.h"

#include <iostream>


#ifdef _WIN32
#include "resource.h"
// windows code goes here
#include <windows.h>

int  main(int argc, char* argv[]);
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	return main(__argc, __argv);
}
#endif
int main(int argc, char* argv[])
{
	
		Game game;
		game.run();
	return 0;
}


