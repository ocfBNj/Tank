#pragma once

#include <graphics.h>
#include "struct.h"
#include "TankBase.h"
#include "Timer.h"
#include "Sound.h"

class TankBase;
class Bullet {
public:
	Bullet();
	void shoot(const TankBase& tank, bool is_enemy); //发射子弹
	bool move();                                     //移动子弹
	bool isExist() const;                            //获得子弹存在信息
	int getRealX() const;                            //获得子弹实际坐标
	int getRealY() const;
	int getHeight() const;
	int getWidth() const;
	Dir getDir() const;
	void adjust();                                   //碰撞后清理子弹
private:
	IMAGE img_bullet[4];                             //子弹图片
	int x, y;                                        //子弹（左上角）显示坐标
	int real_x, real_y;                              //子弹（左上角）实际坐标
	Dir dir;                                         //方向
	int speed;                                       //子弹速度
	bool exist;                                      //子弹是否存在
	Timer timer_shoot;                               //敌人发射子弹频率

	void clearOld() const;                           //清理残留贴图
};
