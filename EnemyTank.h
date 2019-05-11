#pragma once

#include "TankBase.h"
#include "Timer.h"

enum EnemyType {
	ORDINARY, TOPSPEED, SPEEDGUN, ARMOURED
};

enum EnemyTarget {
	PLAYER, CAMP
};

class EnemyTank : public TankBase {
public:
	EnemyTank(int, int, EnemyType, EnemyTarget);
	void move(int _x, int _y);
	void show();
	void changeDir(int, int);
	void changeDirToPlayer(int, int);
	void changeDirToCamp();
private:
	EnemyType type;                        //坦克类型
	EnemyTarget target;                    //敌方坦克攻击目标
	IMAGE img_gray[4][4][2];               //坦克贴图

	Timer timer_move;
	Timer timer_dir;
};

