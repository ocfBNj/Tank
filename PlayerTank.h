#pragma once

#include <conio.h>
#include "TankBase.h"

class PlayerTank : public TankBase {
	friend class GameControl;
public:
	PlayerTank();
	void moveToStart();            //移动到初始位置
private:
	void move();                   //坦克移动
	void show();                   //显示坦克

	IMAGE img_player[4][2];        //玩家坦克图片
};