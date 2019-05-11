#pragma once

// 传入地图，判断两个矩形是否相交
#include "Map.h"
#include <memory>
#include <list>
#include "Bullet.h"
#include "PlayerTank.h"
#include "EnemyTank.h"

class HitDection {
	friend class GameControl;
public:
	HitDection(Map&);
	~HitDection() = default;

	bool isIntersect(                              //判断两个矩形是否相交
		int x1, int y1, int w1, int h1,
		int x2, int y2, int w2, int h2);
private:
	bool blockDection(int x, int y, int w, int h);      //判断子弹是否与墙相撞
	void canGo(std::shared_ptr<TankBase>);         //判断坦克能不能走

	void playerDection(std::shared_ptr<TankBase>, //判断玩家撞墙和撞敌人
		std::list<std::pair<std::shared_ptr<EnemyTank>, std::shared_ptr<Bullet>>>&);

	void enemyDection(std::shared_ptr<TankBase>,  //判断敌人撞墙,撞敌人,撞玩家
		std::shared_ptr<TankBase>,
		std::list<std::pair<std::shared_ptr<EnemyTank>, std::shared_ptr<Bullet>>>&);

	int focus(                                     //判断子弹是否击中坦克
		std::shared_ptr<PlayerTank>&,
		std::shared_ptr<Bullet>&,
		std::list<std::pair<std::shared_ptr<EnemyTank>, std::shared_ptr<Bullet>>>&);
	void bulletDection(std::shared_ptr<Bullet>&,   //判断子弹相撞
		std::shared_ptr<Bullet>&);
private:
	Map& map;                                      //地图
	int map_x, map_y;                              //比较相撞时地图的左上角坐标
	bool hit_flag;                                 //撞击标志，撞击后提示地图更新
};