#pragma once

// 传入地图，判断两个矩形是否相交
#include "Map.h"
#include <memory>
#include <list>
#include "Bullet.h"
#include "PlayerTank.h"
#include "EnemyTank.h"

class HitDection
{
	friend class GameControl;

	HitDection(Map&);
	~HitDection() = default;

	bool isIntersect(                              //判断两个矩形是否相交
		int x1, int y1, int w1, int h1,
		int x2, int y2, int w2, int h2);
	bool dection(int x, int y, int w, int h);      //判断子弹是否与墙相撞
	void canGo(int& x, int& y, Dir d);             //判断坦克能不能走
	int focus(                                     //判断子弹是否击中坦克
		std::shared_ptr<TankBase>&,
		std::shared_ptr<Bullet>&,
		std::list<std::shared_ptr<TankBase>>&,
		std::list<std::shared_ptr<Bullet>>&);

	Map& map;                                      //地图
	int map_x, map_y;                              //比较相撞时地图的左上角坐标
	bool hit_flag;                                 //撞击标志，撞击后提示地图更新
};