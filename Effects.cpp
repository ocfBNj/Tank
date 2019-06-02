#include "Effects.h"

Effects::Effects() : cur(0){
	loadimage(&blast[0], _T(".\\res\\image\\bumb1.gif"));
	loadimage(&blast[1], _T(".\\res\\image\\bumb2.gif"));
	loadimage(&blast[2], _T(".\\res\\image\\bumb3.gif"));
}

void Effects::makeEffects(int x, int y) {
	transparentimage(NULL, x, y, &blast[cur], 0xffc4c4);
}

bool Effects::change() {
	cur++;
	if (cur > 3) {
		cur = 0;
		return false;
	} else {
		return true;
	}
}
