#include "GameControl.h"

GameControl::GameControl() :
	map(new Map),
	playerTank(new PlayerTank(
		CENTER_X + 8 * BLOCK_SIZE, CENTER_Y + 24 * BLOCK_SIZE)),
	playerBullet(new Bullet), hit(*map), enemies_total(20)
{
	loadimage(&bumb_img[0], _T(".\\res\\image\\bumb1.gif"));
	loadimage(&bumb_img[1], _T(".\\res\\image\\bumb2.gif"));
	loadimage(&bumb_img[2], _T(".\\res\\image\\bumb3.gif"));

	addEnemy();
	addEnemy();
	addEnemy();
}

void GameControl::gameLoop() {
	soundManager.playMusic(START);//播放开始游戏音乐

	while (enemies_total) {
		//移动玩家
		playerTank->move();
		hit.player_dection(playerTank, enemies);
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
			if (playerBullet->move()) {
				soundManager.playMusic(BIN);
				//blast(playerBullet->x, playerBullet->y);
			}


		}

		/**************************************************************************************************************/

		//移动敌方坦克并发射,移动子弹
		for (auto& enemy : enemies) {
			enemy.first->changeDir(playerTank->x, playerTank->y);//改变敌方坦克方向
			enemy.first->move();
			hit.enemy_dection(enemy.first, playerTank, enemies);
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
		auto ret = hit.focus(playerTank, playerBullet, enemies);
		if (ret == 1) {//子弹击中敌人
			soundManager.playMusic(ENEMY_DIE);
			enemies_total--;
			addEnemy();
		}
		else if (ret == 2) {//玩家被击中
			playerTank->clearOld();
			FlushBatchDraw();
			soundManager.playMusic(PLAYER_DIE);
			Sleep(2000);
			return;
		}

		//更新地图
		map->showMap();
		FlushBatchDraw();
		Sleep(3);
	}
}

inline
void GameControl::addEnemy() {
	static size_t id = 0;
	if (id == 20)return;
	std::shared_ptr<EnemyTank> tank(new EnemyTank(CENTER_X + id % 3 * 12 * BLOCK_SIZE, CENTER_Y, (EnemyType)(rand() % 4)));
	std::shared_ptr<Bullet> bullet(new Bullet);
	std::pair<std::shared_ptr<EnemyTank>, std::shared_ptr<Bullet>> enemy(tank, bullet);
	enemies.push_back(enemy);
	++id;
}

void GameControl::blast(int x, int y) {
	static int n = 0;
	if (n == 0) {
		getimage(&temp, x, y, x + BLOCK_SIZE * 2, y + BLOCK_SIZE * 2);
	}
	else if (n > 2) {
		putimage(x, y, &temp);
		n = 0;
		return;
	}
	transparentimage(NULL, x - BLOCK_SIZE, y - BLOCK_SIZE, &bumb_img[n++], 0xffc4c4);
}