#pragma once

#include "struct.h"
#include "Timer.h"

class TankBase {
	friend class GameControl;
	friend class HitDection;
public:
	TankBase(int _x, int _y, Dir d, int s, int b);
	virtual ~TankBase() = default;
protected:
	virtual void move() = 0;          //坦克移动
	virtual void show() = 0;          //显示坦克
	void changeShape();               //切换造型
	void auto_move();                 //开启自动移动
	void clearOld();                  //清理旧图

	int x, y;                         //坦克（左上角）坐标
	Dir dir;                          //方向
	bool auto_flag;                   //自动移动标记
	int speed;                        //坦克速度
	int cur_shape;                    //当前造型
	int blood;                        //坦克血量
	Timer t;                          //计时器
};

