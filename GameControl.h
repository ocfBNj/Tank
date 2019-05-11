#ifndef _GAME_CONTROL_
#define _GAME_CONTROL_

#include <graphics.h>
#include "struct.h"
#include "Map.h"
#include "PlayerTank.h"
#include "Bullet.h"
#include "HitDection.h"

class GameControl {
public:
	GameControl();
	void gameLoop();                     //游戏主循环
private:
	Map map;                             //地图
	HitDection hit;                      //碰撞检测
	PlayerTank player;                   //玩家
	Bullet bullet_player;                //玩家子弹

	void updatePlayer();
};

#endif // !_GAME_CONTROL_