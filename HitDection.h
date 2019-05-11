#ifndef _HIT_DECTION_H_
#define _HIT_DECTION_H_

#include "TankBase.h"
#include "Map.h"
#include "Bullet.h"

class Map;
class TankBase;
class Bullet;
class HitDection {
public:
	HitDection();
	bool isIntersect(                                   //判断两个矩形是否相交
		int x1, int y1, int w1, int h1,
		int x2, int y2, int w2, int h2) const;
	void tankMove(TankBase& tank, Map& map);            //检测坦克撞墙
	void hitWall(Bullet& blt, Map& map);
private:
	int map_x, map_y;                                   //比较相撞时地图的左上角坐标
};

#endif // !_HIT_DECTION_H_