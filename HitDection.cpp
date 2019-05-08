#include "HitDection.h"

HitDection::HitDection(Map& m) :
	map(m), map_x(), map_y(),
	hit_flag(false) {}

bool HitDection::isIntersect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	//判断是否相交
	//判断不相交的情况，然后取反就是相交的情况
	return !(x1 + w1 <= x2 || y1 + h1 <= y2 || x2 + w2 <= x1 || y2 + h2 <= y1);
}

bool HitDection::blockDection(int x, int y, int w, int h) {
	bool flag = false;
	//两个矩形是否相交
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			//只有墙可以消除
			if (map.map[i][j] == '0') continue;
			//左上角坐标
			map_x = j * BLOCK_SIZE + CENTER_X;
			map_y = i * BLOCK_SIZE + CENTER_Y;

			if (isIntersect(map_x, map_y, BLOCK_SIZE, BLOCK_SIZE, x, y, w, h)) {
				if (map.map[i][j] == '3')
					map.map[i][j] = 100;//是墙，消除
				flag = true;
			}
		}
	}
	return flag;
}

void HitDection::canGo(std::shared_ptr<TankBase> tank)
{
	//判断是否撞墙
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			if (map.map[i][j] == '0') continue;
			//左上角坐标
			map_x = j * BLOCK_SIZE + CENTER_X;
			map_y = i * BLOCK_SIZE + CENTER_Y;

			if (isIntersect(map_x, map_y, BLOCK_SIZE, BLOCK_SIZE, tank->x, tank->y, BLOCK_SIZE * 2, BLOCK_SIZE * 2)) {
				if (tank->dir == UP) tank->y += tank->speed;
				else if (tank->dir == DOWN)tank->y -= tank->speed;
				else if (tank->dir == LEFT) tank->x += tank->speed;
				else if (tank->dir == RIGHT) tank->x -= tank->speed;

				return;
			}
		}
	}
}

void HitDection::playerDection(std::shared_ptr<TankBase> player,
	std::list<std::pair<std::shared_ptr<EnemyTank>, std::shared_ptr<Bullet>>> & enemies)
{
	canGo(player);
	for (auto& enemy : enemies) {
		if (isIntersect(player->x, player->y, BLOCK_SIZE * 2, BLOCK_SIZE * 2,
			enemy.first->x, enemy.first->y, BLOCK_SIZE * 2, BLOCK_SIZE * 2)) {
			if (player->dir == UP) player->y += player->speed;
			else if (player->dir == DOWN)player->y -= player->speed;
			else if (player->dir == LEFT) player->x += player->speed;
			else if (player->dir == RIGHT) player->x -= player->speed;
			return;
		}
	}
}

void HitDection::enemyDection(std::shared_ptr<TankBase> enemy, std::shared_ptr<TankBase> player,
	std::list<std::pair<std::shared_ptr<EnemyTank>, std::shared_ptr<Bullet>>> & enemies)
{
	canGo(enemy);
	//判断是否撞到玩家
	if (isIntersect(player->x, player->y, BLOCK_SIZE * 2, BLOCK_SIZE * 2,
		enemy->x, enemy->y, BLOCK_SIZE * 2, BLOCK_SIZE * 2))
	{
		if (enemy->dir == UP) enemy->y += enemy->speed;
		else if (enemy->dir == DOWN)enemy->y -= enemy->speed;
		else if (enemy->dir == LEFT) enemy->x += enemy->speed;
		else if (enemy->dir == RIGHT) enemy->x -= enemy->speed;
		return;
	}
	//判断是否撞到敌人
	for (auto& tank : enemies) {
		if (enemy == tank.first) continue;
		if (isIntersect(enemy->x, enemy->y, BLOCK_SIZE * 2, BLOCK_SIZE * 2,
			tank.first->x, tank.first->y, BLOCK_SIZE * 2, BLOCK_SIZE * 2))
		{
			if (enemy->dir == UP) enemy->y += enemy->speed;
			else if (enemy->dir == DOWN)enemy->y -= enemy->speed;
			else if (enemy->dir == LEFT) enemy->x += enemy->speed;
			else if (enemy->dir == RIGHT) enemy->x -= enemy->speed;
			return;
		}
	}
}

int HitDection::focus(std::shared_ptr<PlayerTank> & pl_tank,
	std::shared_ptr<Bullet> & pl_blt,
	std::list<std::pair<std::shared_ptr<EnemyTank>, std::shared_ptr<Bullet>>> & enemies)
{

	for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++) {
		//判断玩家的子弹是否击中敌人
		if (pl_blt->exist && isIntersect(pl_blt->x, pl_blt->y, 12, 12, enemy->first->x, enemy->first->y, BLOCK_SIZE * 2, BLOCK_SIZE * 2)) {
			//掉血
			enemy->first->blood--;
			//清理子弹
			pl_blt->exist = false;
			pl_blt->clearOld();
			//清理敌人
			if (enemy->first->blood <= 0) {
				enemy->first->clearOld();
				enemy->second->clearOld();
				enemies.erase(enemy);
				return 1;//击中并且死亡
			}
			return 0;//击中但未死亡
		}
		//判断敌人的子弹是否击中玩家
		if (enemy->second->exist && isIntersect(enemy->second->x, enemy->second->y, 12, 12, pl_tank->x, pl_tank->y, BLOCK_SIZE * 2, BLOCK_SIZE * 2)) {
			pl_tank->blood--;
			pl_tank->clearOld();
			pl_blt->exist = false;
			pl_blt->clearOld();
			if (pl_tank->blood <= 0)
				return 3;//击中并且死亡
			return 2;//击中但未死亡
		}
	}
	return -1;
}

void HitDection::bulletDection(std::shared_ptr<Bullet>& player_bullet,
	std::shared_ptr<Bullet>& enemy_bullet)
{
	if (isIntersect(player_bullet->x, player_bullet->y, 12, 12,
		enemy_bullet->x, enemy_bullet->y, 12, 12))
	{
		player_bullet->exist = false;
		enemy_bullet->exist = false;
		player_bullet->clearOld();
		enemy_bullet->clearOld();
	}

}
