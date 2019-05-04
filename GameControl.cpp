#include "GameControl.h"

GameControl::GameControl() :
	map(new Map),
	playerTank(new PlayerTank(
		CENTER_X + 8 * BLOCK_SIZE, CENTER_Y + 24 * BLOCK_SIZE)),
	playerBullet(new Bullet), hit(*map)
{
	addEnemy();

}

void GameControl::gameLoop() {
	soundManager.playMusic(START);//播放开始游戏音乐
	auto enemy_beg = enemiesTank.begin();
	auto blt_beg = enemiesBullet.begin();

	while (true) {
		//移动玩家
		playerTank->move();
		hit.canGo(playerTank->x, playerTank->y, playerTank->dir);
		playerTank->show();

		//玩家发射子弹
		if (playerBullet->shoot(playerTank->x, playerTank->y, playerTank->dir, false))
			soundManager.playMusic(SHOOT);

		//移动玩家子弹
		if (playerBullet->exist) {
			//检测子弹是否碰到地图
			if (hit.dection(playerBullet->x, playerBullet->y, 12, 12)) {
				playerBullet->clearOld();
				playerBullet->exist = false;
			}
			//检测子弹是否碰到边缘
			if (playerBullet->move())
				soundManager.playMusic(BIN);

		}

		/**************************************************************************************************************/

		//移动敌方坦克并发射子弹
		enemy_beg = enemiesTank.begin();
		blt_beg = enemiesBullet.begin();
		for (; enemy_beg != enemiesTank.end() && blt_beg != enemiesBullet.end(); ++enemy_beg, ++blt_beg) {

			if ((*enemy_beg)->blood > 0) {
				(*enemy_beg)->move();
				hit.canGo((*enemy_beg)->x, (*enemy_beg)->y, (*enemy_beg)->dir);
				(*enemy_beg)->show();
				(*blt_beg)->shoot((*enemy_beg)->x, (*enemy_beg)->y, (*enemy_beg)->dir, true);
			}

		}

		//移动敌方坦克子弹
		for (auto& bullet : enemiesBullet) {
			if (bullet->exist) {
				if (hit.dection(bullet->x, bullet->y, 12, 12)) {
					bullet->clearOld();
					bullet->exist = false;
				}
				bullet->move();
			}
		}
		/**************************************************************************************************************/

		//判断子弹与坦克是否相撞
		hit.focus(playerTank, playerBullet, enemiesTank, enemiesBullet);

		//更新地图
		map->showMap();
		FlushBatchDraw();
		Sleep(3);
	}
}

void GameControl::addEnemy() {
	std::shared_ptr<TankBase> tank(new EnemyTank(CENTER_X, CENTER_Y, ORDINARY));
	std::shared_ptr<Bullet> bullet(new Bullet);
	enemiesTank.push_back(tank);
	enemiesBullet.push_back(bullet);
}