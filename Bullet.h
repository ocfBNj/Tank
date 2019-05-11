#pragma once

#include <graphics.h>
#include "struct.h"
#include "TankBase.h"
#include "Timer.h"

class TankBase;
class Bullet {
public:
	Bullet();
	void shoot(const TankBase& tank, bool is_enemy); //发射子弹
	bool move();                                     //移动子弹
	bool isExist() const;                            //获得子弹存在信息
	int getX() const;
	int getY() const;
	void adjust();                                   //碰撞和清理子弹
private:
	IMAGE img_bullet[4];                             //子弹图片
	int x, y;                                        //子弹（左上角）坐标
	Dir dir;                                         //方向
	int speed;                                       //子弹速度
	bool exist;                                      //子弹是否存在
	Timer timer_shoot;                               //敌人发射子弹频率

	void clearOld() const;                           //清理残留贴图
};
