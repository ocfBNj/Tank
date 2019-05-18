#pragma once

#include <conio.h>
#include "TankBase.h"
#include "Sound.h"

class PlayerTank : public TankBase {
public:
	PlayerTank();
	void moveToStart();            //移动到初始位置
	void move();                   //坦克移动
	void show();                   //显示坦克
private:
	IMAGE img_player[4][2];        //玩家坦克图片
};