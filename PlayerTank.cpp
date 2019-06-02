#include "PlayerTank.h"

PlayerTank::PlayerTank() :
	TankBase(CENTER_X + 8 * BLOCK_SIZE, CENTER_Y + 24 * BLOCK_SIZE, UP, 1, 3) {
	//加载图片
	loadimage(&img_player[LEFT][0], _T(".\\res\\image\\0Player\\m0-0-1.gif"));
	loadimage(&img_player[LEFT][1], _T(".\\res\\image\\0Player\\m0-0-2.gif"));
	loadimage(&img_player[UP][0], _T(".\\res\\image\\0Player\\m0-1-1.gif"));
	loadimage(&img_player[UP][1], _T(".\\res\\image\\0Player\\m0-1-2.gif"));
	loadimage(&img_player[RIGHT][0], _T(".\\res\\image\\0Player\\m0-2-1.gif"));
	loadimage(&img_player[RIGHT][1], _T(".\\res\\image\\0Player\\m0-2-2.gif"));
	loadimage(&img_player[DOWN][0], _T(".\\res\\image\\0Player\\m0-3-1.gif"));
	loadimage(&img_player[DOWN][1], _T(".\\res\\image\\0Player\\m0-3-2.gif"));

	//将坦克放在初始位置
	moveToStart();
	//putimage(x, y, &img_player[dir][cur_shape]);
}

void PlayerTank::moveToStart() {
	clearOld();
	x = CENTER_X + 8 * BLOCK_SIZE;
	y = CENTER_Y + 24 * BLOCK_SIZE;
}

void PlayerTank::move() {
	changeShape();
	if (flag_move == false) {
		if (GetAsyncKeyState('W') & 0x8000) {
			flag_move = true;
			dir = UP;
		} else if (GetAsyncKeyState('S') & 0x8000) {
			flag_move = true;
			dir = DOWN;
		} else if (GetAsyncKeyState('A') & 0x8000) {
			flag_move = true;
			dir = LEFT;
		} else if (GetAsyncKeyState('D') & 0x8000) {
			flag_move = true;
			dir = RIGHT;
		}
	} else {
		autoMove();
	}
}

void PlayerTank::show() {
	transparentimage(NULL, x, y, &img_player[dir][cur_shape], 0xffc4c4);
}