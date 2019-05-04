#include "EnemyTank.h"


EnemyTank::EnemyTank(int x, int y, EnemyType t) :
	TankBase(x, y, DOWN, 1, 1), type(t)
{
	//ÆÕÍ¨Ì¹¿Ë
	if (type == ORDINARY) {
		auto_flag = true;
		loadimage(&img_gray[ORDINARY][LEFT][0], _T(".\\res\\image\\gray-tank\\1-1-1.gif"));
		loadimage(&img_gray[ORDINARY][LEFT][1], _T(".\\res\\image\\gray-tank\\1-1-2.gif"));
		loadimage(&img_gray[ORDINARY][UP][0], _T(".\\res\\image\\gray-tank\\1-2-1.gif"));
		loadimage(&img_gray[ORDINARY][UP][1], _T(".\\res\\image\\gray-tank\\1-2-2.gif"));
		loadimage(&img_gray[ORDINARY][RIGHT][0], _T(".\\res\\image\\gray-tank\\1-3-1.gif"));
		loadimage(&img_gray[ORDINARY][RIGHT][1], _T(".\\res\\image\\gray-tank\\1-3-2.gif"));
		loadimage(&img_gray[ORDINARY][DOWN][0], _T(".\\res\\image\\gray-tank\\1-4-1.gif"));
		loadimage(&img_gray[ORDINARY][DOWN][1], _T(".\\res\\image\\gray-tank\\1-4-2.gif"));
	}

}


void EnemyTank::move() {
	/*t.stop();
	if (t.times() >= 2) {
		dir = (Dir)(rand() % 4);
		t.start();
	}*/
	auto_move();
}

void EnemyTank::show() {
	if (blood) {
		transparentimage(NULL, x, y, &img_gray[type][dir][cur_shape], 0xffc4c4);
		changeShape();
	}
}
