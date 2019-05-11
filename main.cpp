#include "struct.h"
#include "SelectPanel.h"
#include "GameControl.h"

int main(void) {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	BeginBatchDraw();

	SelectPanel select;
	select.select();

	GameControl game;
	game.gameLoop();


	return 0;
}