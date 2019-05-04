#include "TankBase.h"

TankBase::TankBase(int _x, int _y, Dir d, int s, int b) :
	x(_x), y(_y), dir(d),
	auto_flag(false), speed(s),
	cur_shape(0), blood(b) {}

void TankBase::changeShape() {
	if (cur_shape)
		cur_shape = 0;
	else
		cur_shape = 1;
}

void TankBase::auto_move() {
	static int steep = 0;
	t.stop();
	if (auto_flag && t.times() >= 6) {
		t.start();
		steep++;
		if (steep == BLOCK_SIZE) {
			auto_flag = false;
			steep = 0;
		}
		switch (dir)
		{
		case UP:
			//碰到边界
			if (y - speed < CENTER_Y)
				return;
			clearOld();//清理残留图片
			y -= speed;
			break;
		case DOWN:
			if (y + BLOCK_SIZE * 2 + speed > CENTER_Y + CENTER_HEIGHT)
				return;
			clearOld();
			y += speed;
			break;
		case LEFT:
			if (x - speed < CENTER_X)
				return;
			clearOld();
			x -= speed;
			break;
		case RIGHT:
			if (x + BLOCK_SIZE * 2 + speed > CENTER_X + CENTER_WIDTH)
				return;
			clearOld();
			x += speed;
			break;
		default:
			break;
		}
		
	}
}

inline
void TankBase::clearOld() {
	clearrectangle(x, y, x + BLOCK_SIZE * 2 - 1, y + BLOCK_SIZE * 2 - 1);
}