#pragma once

#include "TankBase.h"

enum EnemyType {
	ORDINARY, TOPSPEED, SPEEDGUN, ARMOURED
};

enum EnemyTarget {
	PLAYER, CAMP
};

class EnemyTank : public TankBase {
	friend class GameControl;
	friend class HitDection;
public:
	EnemyTank(int, int, EnemyType, EnemyTarget);
private:
	void move();
	void show();
	void changeDir(int, int);
	void changeDirToPlayer(int, int);
	void changeDirToCamp();

	EnemyType type;                        //坦克类型
	EnemyTarget target;                    //敌方坦克攻击目标
	IMAGE img_gray[4][4][2];               //坦克贴图
	Timer dir_timer;
	Timer move_timer;
};

