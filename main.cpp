#include "struct.h"
#include "SelectPanel.h"
#include "GameControl.h"
#include "Sound.h"

int main(void) {
	srand((unsigned)time(NULL));
	Sound::init();
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	BeginBatchDraw();

	SelectPanel select;
	select.select();

	GameControl game;
	game.gameLoop();


	return 0;
}