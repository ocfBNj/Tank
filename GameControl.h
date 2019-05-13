#ifndef _GAME_CONTROL_
#define _GAME_CONTROL_

#include <graphics.h>
#include <list>
#include <iterator>
#include <ctime>
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
	size_t enemies_total;                //敌方坦克总数
	size_t born_total;                   //已经出生的地方坦克总数

	void updatePlayer();                 //更新玩家数据
	void updataEnemies();                //更新敌人数据
	void addEnemy();                     //增加一辆地方坦克
};

#endif // !_GAME_CONTROL_