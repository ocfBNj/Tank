#ifndef _HIT_DECTION_H_
#define _HIT_DECTION_H_

#include <list>
#include "TankBase.h"
#include "Map.h"
#include "Bullet.h"
#include "EnemyTank.h"
#include "PlayerTank.h"
#include "Sound.h"

class Map;
class TankBase;
class Bullet;
class HitDection {
public:
	bool isIntersect(                                         //判断两个矩形是否相交
		int x1, int y1, int w1, int h1,
		int x2, int y2, int w2, int h2) const;
	bool isIntersect(TankBase &tank1, TankBase &tank2);       //判断两个坦克是否相交
	void noKnockWall(TankBase& tank, Map& map);               //防止坦克撞墙
	void hitWall(Bullet& blt, Map& map);                      //子弹击中墙
	void impactTank(TankBase& tank1, TankBase& tank2);        //tank1撞tank2
	void focusBullet(TankBase& pl_tank, Bullet& pl_blt,       //子弹击中（坦克或子弹）
		std::list<EnemyTank>& enemies_tank, std::list<Bullet>& enemies_blt);
};

#endif // !_HIT_DECTION_H_