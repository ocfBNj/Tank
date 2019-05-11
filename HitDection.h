#ifndef _HIT_DECTION_H_
#define _HIT_DECTION_H_

#include <list>
#include "TankBase.h"
#include "Map.h"
#include "Bullet.h"
#include "EnemyTank.h"

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
	void hitWall(Bullet& blt, Map& map);                //子弹击中墙
	void hitTank(TankBase& tank1, TankBase& tank2);     //tank1撞tank2
	void focusTank(TankBase& pl_tank, Bullet& pl_blt,   //子弹击中坦克
		std::list<EnemyTank>& enemies_tank, std::list<Bullet>& enemies_blt); 
private:
	int map_x, map_y;                                   //比较相撞时地图的左上角坐标
};

#endif // !_HIT_DECTION_H_