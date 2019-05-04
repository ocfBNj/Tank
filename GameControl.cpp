#include "GameControl.h"

GameControl::GameControl() :
	map(new Map),
	playerTank(new PlayerTank(
		CENTER_X + 8 * BLOCK_SIZE, CENTER_Y + 24 * BLOCK_SIZE)),
	playerBullet(new Bullet), hit(*map), enemies_total(20)
{
	addEnemy();
	addEnemy();
	addEnemy();

}

void GameControl::gameLoop() {
	soundManager.playMusic(START);//播放开始游戏音乐

	while (enemies_total) {
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

		//移动敌方坦克并发射,移动子弹
		for (auto& enemy : enemies) {
			enemy.first->move();
			hit.canGo(enemy.first->x, enemy.first->y, enemy.first->dir);
			enemy.first->show();
			t.stop();
			if (!enemy.second->exist && t.times() >= 500) {
				enemy.second->shoot(enemy.first->x, enemy.first->y, enemy.first->dir, true);
				t.start();
			}
			//移动子弹
			if (enemy.second->exist) {
				if (hit.dection(enemy.second->x, enemy.second->y, 12, 12)) {
					enemy.second->clearOld();
					enemy.second->exist = false;
				}
				enemy.second->move();
			}
		}
		/**************************************************************************************************************/

		//判断子弹与坦克是否相撞
		if (hit.focus(playerTank, playerBullet, enemies) == 1) {
			enemies_total--;
			addEnemy();
		}

		//更新地图
		map->showMap();
		FlushBatchDraw();
		Sleep(3);
	}
}

void GameControl::addEnemy() {
	static size_t id = 0;
	std::shared_ptr<TankBase> tank(new EnemyTank(CENTER_X + id % 3 * 12 * BLOCK_SIZE, CENTER_Y, (EnemyType)(rand() % 4)));
	std::shared_ptr<Bullet> bullet(new Bullet);
	std::pair<std::shared_ptr<TankBase>, std::shared_ptr<Bullet>> enemy(tank, bullet);
	enemies.push_back(enemy);
	++id;
}