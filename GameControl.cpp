#include "GameControl.h"

GameControl::GameControl() {}

void GameControl::gameLoop() {
	map.showMap();
	while (true) {
		updatePlayer();


		map.update();
		FlushBatchDraw();
		Sleep(5);
	}
}

inline void GameControl::updatePlayer() {
	player.move();
	if (player.isMoving()) hit.tankMove(player, map);
	player.show();

	bullet_player.shoot(player, false);
	if (bullet_player.isExist()) {
		hit.hitWall(bullet_player, map);
		bullet_player.move();
	}

}