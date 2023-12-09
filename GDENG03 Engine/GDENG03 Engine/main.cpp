/*
Group 4
GDENG03 XX22
MCO: Scene Editor
*/

#include"AppWindow.h"

int main() {
	AppWindow game;

	if (game.initialize()) {
		while (game.isRunning()) {
			game.broadcast();
		}
	}

	return 0;
}