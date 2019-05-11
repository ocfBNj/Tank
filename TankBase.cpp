#include "TankBase.h"

TankBase::TankBase(int _x, int _y, Dir d, int s, int b) :
	x(_x), y(_y), dir(d),
	flag_move(false), speed(s),
	cur_blood(b), cur_shape(0), steep(0) {}

int TankBase::getX() const {
	return x;
}

int TankBase::getY() const {
	return y;
}

Dir TankBase::getDir() const {
	return dir;
}

void TankBase::adjust() {
	if (dir == UP)y += speed;
	else if (dir == DOWN) y -= speed;
	else if (dir == LEFT) x += speed;
	else if (dir == RIGHT) x -= speed;

	stopMove();
}

bool TankBase::isMoving() {
	return flag_move;
}

void TankBase::changeShape() {
	if (cur_shape)
		cur_shape = 0;
	else
		cur_shape = 1;
}

void TankBase::autoMove() {
	if (steep == BLOCK_SIZE) {
		stopMove();
		return;
	}
	clearOld();
	switch (dir) {
	case UP:
		if (y - speed < CENTER_Y) { //Åöµ½±ß½ç
			stopMove();
			return; 
		}
		y -= speed;
		break;
	case DOWN:
		if (y + BLOCK_SIZE * 2 + speed > CENTER_Y + CENTER_HEIGHT) {
			stopMove();
			return;
		}
		y += speed;
		break;
	case LEFT:
		if (x - speed < CENTER_X) {
			stopMove();
			return;
		}
		x -= speed;
		break;
	case RIGHT:
		if (x + BLOCK_SIZE * 2 + speed > CENTER_X + CENTER_WIDTH) {
			stopMove();
			return;
		}
		x += speed;
		break;
	default:
		break;
	}
	steep += speed;
}

inline void TankBase::stopMove() {
	flag_move = false;
	steep = 0;
}

inline void TankBase::clearOld() const {
	clearrectangle(x, y, x + BLOCK_SIZE * 2 - 1, y + BLOCK_SIZE * 2 - 1);
}