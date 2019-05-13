#include "HitDection.h"

bool HitDection::isIntersect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) const {
	return !(x1 + w1 <= x2 || y1 + h1 <= y2 || x2 + w2 <= x1 || y2 + h2 <= y1);
}

void HitDection::noKnockWall(TankBase & tank, Map & map) {
	//判断是否撞墙
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			if (map.map[i][j] == '0') continue;
			//左上角坐标
			int map_x = j * BLOCK_SIZE + CENTER_X;
			int map_y = i * BLOCK_SIZE + CENTER_Y;
			if (isIntersect(map_x, map_y, BLOCK_SIZE, BLOCK_SIZE,
				tank.getX(), tank.getY(), BLOCK_SIZE * 2, BLOCK_SIZE * 2)) {
				tank.adjust();
				return;
			}
		}
	}
}

void HitDection::hitWall(Bullet & blt, Map & map) {
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			if (map.map[i][j] == '0') continue;
			//左上角坐标
			int map_x = j * BLOCK_SIZE + CENTER_X;
			int map_y = i * BLOCK_SIZE + CENTER_Y;
			if (isIntersect(map_x, map_y, BLOCK_SIZE, BLOCK_SIZE,
				blt.getX(), blt.getY(), BULLET_SIZE, BULLET_SIZE)) {
				map.adjust(i, j);
				blt.adjust();
			}
		}
	}
}

void HitDection::impactTank(TankBase & tank1, TankBase & tank2) {
	if (isIntersect(tank1.getX(), tank1.getY(), BLOCK_SIZE * 2, BLOCK_SIZE * 2,
		tank2.getX(), tank2.getY(), BLOCK_SIZE * 2, BLOCK_SIZE * 2)) {
		tank1.adjust();
		return;
	}
}

void HitDection::focusBullet(TankBase & player, Bullet & pl_blt,
	std::list<EnemyTank> & enemies, std::list<Bullet> & enemies_blt) {

	auto enemy = enemies.begin();
	auto enemy_blt = enemies_blt.begin();

	for (; enemy != enemies.end() && enemy_blt != enemies_blt.end(); enemy++, enemy_blt++) {
		//判断玩家子弹是否击中敌人
		if (pl_blt.isExist() && isIntersect(pl_blt.getX(), pl_blt.getY(), BULLET_SIZE, BULLET_SIZE,
			enemy->getX(), enemy->getY(), BLOCK_SIZE * 2, BLOCK_SIZE * 2)) {

			pl_blt.adjust();
			enemy->disBlood();

			if (enemy->isDied()) {
				enemy->die();
				enemy_blt->adjust();
				enemies_blt.erase(enemy_blt);
				enemies.erase(enemy);
			}
			break;
		}

		//判断子弹与子弹之间相碰
		if (pl_blt.isExist() && enemy_blt->isExist() &&
			isIntersect(pl_blt.getX(), pl_blt.getY(), BULLET_SIZE, BULLET_SIZE,
				enemy_blt->getX(), enemy_blt->getY(), BULLET_SIZE, BULLET_SIZE)) {
			pl_blt.adjust();
			enemy_blt->adjust();
			break;
		}

		//判断敌人子弹是否击中玩家
		if (enemy_blt->isExist() && isIntersect(enemy_blt->getX(), enemy_blt->getY(), BULLET_SIZE, BULLET_SIZE,
			player.getX(), player.getY(), BLOCK_SIZE * 2, BLOCK_SIZE * 2)) {

			enemy_blt->adjust();
			player.disBlood();
			if (player.isDied()) {
				player.die();
			}
			break;
		}
	}
}