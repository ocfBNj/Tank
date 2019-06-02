#include "GameControl.h"

GameControl::GameControl() : enemies_total(20), born_total(0) {}

void GameControl::gameLoop() {
	initGame();
	//敌人全部被消灭并且全部出生则游戏胜利
	while ((enemies.size() != 0) || (born_total != enemies_total)) {
		updatePlayer();
		updataEnemies();

		hit.focusBullet(player, blt_player, enemies, blts_enemies);

		//map.setNeedUpdate(true);
		map.update();

		if (enemies.size() < 3) addEnemy(); //每次生成3辆坦克

		FlushBatchDraw();
		Sleep(6);
	}
}

void GameControl::initGame() {
	map.showMap();
	Sound::play(START);
}

void GameControl::updatePlayer() {
	//更新玩家坦克
	player.move();
	//Sound::pauseMove(player.moveStatus());
	if (player.moveStatus()) {
		hit.noKnockWall(player, map);//坦克与墙碰撞检测
		//坦克与坦克之间碰撞检测
		for (auto &enemy : enemies) {
			hit.impactTank(player, enemy);
		}
	}

	player.show();

	//更新子弹
	blt_player.shoot(player, false);
	if (blt_player.isExist()) {
		hit.hitWall(blt_player, map);
		if (blt_player.move()) Sound::play(BIN);
	}

}

void GameControl::updataEnemies() {
	auto enemy = enemies.begin();
	auto blt = blts_enemies.begin();
	for (; enemy != enemies.end() && blt != blts_enemies.end(); enemy++, blt++) {
		//更新敌方坦克
		enemy->move(player.getX(), player.getY());
		if (enemy->moveStatus()) {
			hit.noKnockWall(*enemy, map);
			hit.impactTank(*enemy, player);

			for (auto i_enemy = enemies.begin(); i_enemy != enemies.end(); i_enemy++) {
				if (enemy == i_enemy)continue;
				hit.impactTank(*enemy, *i_enemy);
			}
		}
		enemy->show();

		//更新子弹
		blt->shoot(*enemy, true);
		if (blt->isExist()) {
			hit.hitWall(*blt, map);
			blt->move();
		}
	}
}

void GameControl::addEnemy() {
	if (born_total == enemies_total) return;
	auto ret = makeNewPos();
	if (std::get<0>(ret) == -1 && std::get<1>(ret) == -1) 
		return; //产生失败

	unsigned type = rand() % 4;
	unsigned des = rand() % 2;
	enemies.push_back(EnemyTank(std::get<0>(ret), std::get<1>(ret),
		static_cast<EnemyType>(type), static_cast<EnemyTarget>(des)));
	blts_enemies.push_back(Bullet());

	born_total++;

}

std::tuple<int, int> GameControl::makeNewPos() {
	int id = rand() % 3;
	int x = CENTER_X + id * 12 * BLOCK_SIZE;
	int y = CENTER_Y;

	//判断该区域是否已有坦克
	for (auto &tank : enemies) {
		if (hit.isIntersect(tank.getX(), tank.getY(), TANK_SIZE, TANK_SIZE,
			x, y, TANK_SIZE, TANK_SIZE)) {
			return std::tuple<int, int>{-1, -1};
		}
	}
	if (hit.isIntersect(player.getX(), player.getY(), TANK_SIZE, TANK_SIZE,
		x, y, TANK_SIZE, TANK_SIZE)) {
		return std::tuple<int, int>{-1, -1};
	}

	return std::tuple<int, int>{x, y};
}