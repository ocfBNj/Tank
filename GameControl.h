#pragma once

#include <graphics.h>
#include <memory>
#include <list>
#include <thread>
#include <iterator>
#include "struct.h"
#include "Map.h"
#include "PlayerTank.h"
#include "EnemyTank.h"
#include "Bullet.h"
#include "HitDection.h"
#include "SoundManager.h"
#include "Timer.h"

class GameControl {
public:
	GameControl();
	void gameLoop();                                      //游戏主循环
private:
	std::shared_ptr<Map> map;                             //地图
	std::shared_ptr<TankBase> playerTank;                 //玩家
	std::shared_ptr<Bullet> playerBullet;                 //玩家子弹
	std::list<std::shared_ptr<TankBase>> enemiesTank;     //敌人列表
	std::list<std::shared_ptr<Bullet>> enemiesBullet;     //敌人子弹列表
	HitDection hit;                                       //碰撞检测
	SoundManager soundManager;                            //管理声音
	Timer t;
	void addEnemy();                                      //增加一辆敌方坦克
};