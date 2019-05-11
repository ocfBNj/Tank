#include "HitDection.h"

HitDection::HitDection() :
	map_x(0), map_y(0) {}

bool HitDection::isIntersect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) const {
	return !(x1 + w1 <= x2 || y1 + h1 <= y2 || x2 + w2 <= x1 || y2 + h2 <= y1);
}

void HitDection::tankMove(TankBase & tank, Map & map) {
	//ÅÐ¶ÏÊÇ·ñ×²Ç½
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			if (map.map[i][j] == '0') continue;
			//×óÉÏ½Ç×ø±ê
			map_x = j * BLOCK_SIZE + CENTER_X;
			map_y = i * BLOCK_SIZE + CENTER_Y;
			if (isIntersect(map_x, map_y, BLOCK_SIZE, BLOCK_SIZE,
				tank.getX(), tank.getY(), BLOCK_SIZE * 2, BLOCK_SIZE * 2)) {
				tank.adjust();
				return;
			}
		}
	}
}

void HitDection::hitWall(Bullet & blt, Map & map) {
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			if (map.map[i][j] == '0') continue;
			//×óÉÏ½Ç×ø±ê
			map_x = j * BLOCK_SIZE + CENTER_X;
			map_y = i * BLOCK_SIZE + CENTER_Y;
			if (isIntersect(map_x, map_y, BLOCK_SIZE, BLOCK_SIZE,
				blt.getX(), blt.getY(), BULLET_SIZE, BULLET_SIZE)) {
				map.adjust(i, j);
				blt.adjust();
			}
		}
	}
}
