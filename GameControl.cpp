#include "GameControl.h"

GameControl::GameControl() : enemies_total(20), born_total(0) {}

void GameControl::gameLoop() {
	map.showMap();
	addEnemy();
	enemies.push_back(EnemyTank(CENTER_X + BLOCK_SIZE * 6, CENTER_Y, ARMOURED, PLAYER));
	blts_enemies.push_back(Bullet());
	while (true) {
		updatePlayer();
		updataEnemies();

		hit.focusBullet(player, blt_player, enemies, blts_enemies);
		map.update();
		FlushBatchDraw();
		Sleep(5);
	}
}

inline void GameControl::updatePlayer() {
	//更新坦克
	player.move();
	if (player.isMoving()) {
		hit.noKnockWall(player, map);//坦克与墙碰撞检测
		//坦克与坦克之间碰撞检测
		for (auto& enemy : enemies) {
			hit.impactTank(player, enemy);
		}
	}
	player.show();

	//更新子弹
	blt_player.shoot(player, false);
	if (blt_player.isExist()) {
		hit.hitWall(blt_player, map);
		blt_player.move();
	}

}

inline void GameControl::updataEnemies() {
	auto enemy = enemies.begin();
	auto blt = blts_enemies.begin();
	for (; enemy != enemies.end() && blt != blts_enemies.end(); enemy++, blt++) {
		//更新坦克
		enemy->move(player.getX(), player.getY());
		if (enemy->isMoving()) {
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
	enemies.push_back(EnemyTank(CENTER_X, CENTER_Y, ARMOURED, PLAYER));
	blts_enemies.push_back(Bullet());

	born_total++;
}