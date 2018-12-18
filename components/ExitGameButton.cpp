#include "components\ExitGameButton.h"
#include "kitten\K_Game.h"

ExitGameButton::ExitGameButton() { }

ExitGameButton::~ExitGameButton() {	}

void ExitGameButton::onClick()
{
	kitten::shutdownGame();
	glfwTerminate();
	exit(EXIT_SUCCESS);
}