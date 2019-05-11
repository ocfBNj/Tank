#pragma once

#include <graphics.h>
#include <Windows.h>
#include "struct.h"
#include "Timer.h"

class Bullet {
	friend class GameControl;
	friend class HitDection;
	Bullet();

	void clearOld();                           //清除当前位置的图片
	bool shoot(int _x, int _y, Dir d, bool b); //发射子弹
	bool move();                               //移动子弹

	IMAGE img_bullet[4];                       //子弹图片
	int x, y;                                  //子弹（左上角）坐标
	Dir dir;                                   //方向
	int speed;                                 //子弹速度
	bool exist;                                //子弹是否存在
	Timer t;                                   //记时器
};
