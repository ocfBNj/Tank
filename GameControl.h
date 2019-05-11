#ifndef _GAME_CONTROL_
#define _GAME_CONTROL_

#include <graphics.h>
#include <list>
#include <iterator>
#include "struct.h"
#include "Map.h"
#include "PlayerTank.h"
#include "EnemyTank.h"
#include "Bullet.h"
#include "HitDection.h"
#include "Timer.h"

class GameControl {
public:
	GameControl();
	void gameLoop();                     //游戏主循环
private:
	Map map;                             //地图
	HitDection hit;                      //碰撞检测
	PlayerTank player;                   //玩家
	Bullet blt_player;                   //玩家子弹
	std::list<EnemyTank> enemies;        //敌人列表
	std::list<Bullet> blts_enemies;      //敌人子弹列表

	void updatePlayer();
	void updataEnemies();
	void addEnemy();
};

#endif // !_GAME_CONTROL_