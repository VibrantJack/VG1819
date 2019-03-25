#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <stdio.h>
#include <stdlib.h>
#include "networking\dedicated_server\ServerGame.h"

#include <atomic>
#include <thread>
#include <iostream>

//========================================================================
// This is needed for newer versions of Visual Studio
//========================================================================
FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}
//========================================================================

void readCin(std::atomic<bool>& run)
{
	std::string buffer;

	while (run.load())
	{
		std::cin >> buffer;

		// quit command to exit
		// would like to add more commands for traditional server actions, ex. kick player, restart
		if (buffer == "quit")
		{
			run.store(false);
		}
	}
}

int main(void)
{
	networking::ServerGame::createInstance();

	// async input/output from stackoverflow
	std::atomic<bool> run(true);
	std::thread cinThread(readCin, std::ref(run));
	while (run.load())
	{
		networking::ServerGame::getInstance()->update();
	}
	run.store(false);
	cinThread.join();

	networking::ServerGame::destroyInstance();

	exit(EXIT_SUCCESS);
}