#include "GameControl.h"

GameControl::GameControl() :
	map(new Map),
	playerTank(new PlayerTank),
	playerBullet(new Bullet), hit(*map),
	enemies_total(20), cur_enemies_total(0)
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
		hit.playerDection(playerTank, enemies);
		playerTank->show();

		//移动玩家子弹
		if (playerBullet->exist) {
			//检测子弹是否碰到地图
			if (hit.blockDection(playerBullet->x, playerBullet->y, 12, 12)) {
				playerBullet->clearOld();
				playerBullet->exist = false;
			}
			//检测子弹是否碰到边缘
			if (playerBullet->move()) {
				soundManager.playMusic(BIN);
				//blast(playerBullet->x, playerBullet->y);
			}

		}

		//玩家发射子弹
		if (playerBullet->shoot(playerTank->x, playerTank->y, playerTank->dir, false))
			soundManager.playMusic(SHOOT);

		

		/**************************************************************************************************************/

		//移动敌方坦克并发射,移动子弹
		for (auto& enemy : enemies) {
			//移动子弹
			if (enemy.second->exist) {
				if (hit.blockDection(enemy.second->x, enemy.second->y, 12, 12)) {
					enemy.second->clearOld();
					enemy.second->exist = false;
				}
				enemy.second->move();
			}

			//改变敌方坦克方向
			if (enemy.first->target == PLAYER)
				enemy.first->changeDirToPlayer(playerTank->x, playerTank->y);
			else if (enemy.first->target == CAMP)
				enemy.first->changeDirToCamp();
			enemy.first->move();
			hit.enemyDection(enemy.first, playerTank, enemies);
			enemy.first->show();
			t.stop();
			if (!enemy.second->exist && t.times() >= 500) {
				enemy.second->shoot(enemy.first->x, enemy.first->y, enemy.first->dir, true);
				t.start();
			}
			
		}
		/**************************************************************************************************************/
		//判断子弹是否相撞
		for (auto& enemy : enemies)
			hit.bulletDection(playerBullet, enemy.second);


		//判断子弹与坦克是否相撞
		auto ret = hit.focus(playerTank, playerBullet, enemies);
		if (ret == 1) {//子弹击败敌人
			soundManager.playMusic(ENEMY_DIE);
			enemies_total--;
			cur_enemies_total--;
		} else if (ret == 0) {//子弹击中敌人
			soundManager.playMusic(BIN);
		} else if (ret == 2) {//玩家被击中
			playerTank->moveToStart();
		} else if (ret == 3) {//玩家被击败
			playerTank->clearOld();
			FlushBatchDraw();
			soundManager.playMusic(PLAYER_DIE);
			Sleep(2000);
			return;
		}

		if (cur_enemies_total < 3)
			addEnemy();

		//更新地图
		map->showMap();
		FlushBatchDraw();
		Sleep(3);
	}
}

inline
void GameControl::addEnemy() {
	static size_t id = 0;//已经出生的敌方坦克总数
	if (id == 20)return;

	//设置地方坦克的目标
	EnemyTarget target;
	if (rand() % 2)
		target = CAMP;
	else
		target = PLAYER;
	//设置坦克出生位置
	int born_x = CENTER_X + id % 3 * 12 * BLOCK_SIZE;
	int born_y = CENTER_Y;
	if (isHaveTank(born_x, born_y))
		return;//不创建坦克

	//创建敌方坦克
	std::shared_ptr<EnemyTank> tank(new EnemyTank(born_x, born_y, (EnemyType)(rand() % 4), target));
	std::shared_ptr<Bullet> bullet(new Bullet);
	std::pair<std::shared_ptr<EnemyTank>, std::shared_ptr<Bullet>> enemy(tank, bullet);
	enemies.push_back(enemy);

	++cur_enemies_total;
	++id;
}

void GameControl::blast(int x, int y) {
	static int n = 0;
	if (n == 0) {
		getimage(&temp, x, y, x + BLOCK_SIZE * 2, y + BLOCK_SIZE * 2);
	} else if (n > 2) {
		putimage(x, y, &temp);
		n = 0;
		return;
	}
	transparentimage(NULL, x - BLOCK_SIZE, y - BLOCK_SIZE, &bumb_img[n++], 0xffc4c4);
}

bool GameControl::isHaveTank(int x, int y) {
	for (auto& enemy : enemies) {
		if (hit.isIntersect(enemy.first->x, enemy.first->y, BLOCK_SIZE * 2, BLOCK_SIZE * 2,
			x, y, BLOCK_SIZE * 2, BLOCK_SIZE * 2))
		{
			return true;
		}
	}
	return false;
}
