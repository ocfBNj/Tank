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
	std::list<std::pair<std::shared_ptr<EnemyTank>,       //敌人
		std::shared_ptr<Bullet>>> enemies;
	HitDection hit;                                       //碰撞检测
	SoundManager soundManager;                            //管理声音
	Timer t;
	size_t enemies_total;                                 //敌方剩余坦克总数

	void addEnemy();                                      //增加一辆敌方坦克
	void blast(int x, int y);                             //爆炸特效

	IMAGE bumb_img[3];                                    //爆炸贴图
	IMAGE temp;                                           //爆炸前该区域的贴图
	Timer bumb_timer;                                     //爆炸时间
};