#include "Map.h"

Map::Map() {
	loadimage(&block_img[WALL], _T(".\\res\\image\\wall.gif"));
	loadimage(&block_img[STONE], _T(".\\res\\image\\stone.gif"));
	loadimage(&block_img[NOR_CAMP], _T(".\\res\\image\\camp0.gif"));
	loadimage(&block_img[DIS_CAMP], _T(".\\res\\image\\camp1.gif"));

	//初始化游戏区域
	setbkcolor(RGB(100, 100, 100));                           //灰色背景
	cleardevice();                                            //将背景设为灰色
	setfillcolor(BLACK);                                      //游戏区域为黑色
	solidrectangle(CENTER_X, CENTER_Y,
		CENTER_X + CENTER_WIDTH, CENTER_Y + CENTER_HEIGHT);
	setbkcolor(BLACK);
}

void Map::showMap() {
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			switch (map[i][j])
			{
			case 100://被子弹撞击的墙
				solidrectangle(CENTER_X + j * BLOCK_SIZE, CENTER_Y + i * BLOCK_SIZE,
					CENTER_X + j * BLOCK_SIZE + BLOCK_SIZE, CENTER_Y + i * BLOCK_SIZE + BLOCK_SIZE);
				map[i][j] = '0';
				break;
			case '1':
				transparentimage(NULL, CENTER_X + j * BLOCK_SIZE, CENTER_Y + i * BLOCK_SIZE, &block_img[NOR_CAMP], 0xffc4c4);
				break;
			case '3':
				transparentimage(NULL, CENTER_X + j * BLOCK_SIZE, CENTER_Y + i * BLOCK_SIZE, &block_img[WALL], 0xffc4c4);
				break;
			case '5':
				transparentimage(NULL, CENTER_X + j * BLOCK_SIZE, CENTER_Y + i * BLOCK_SIZE, &block_img[STONE], 0xffc4c4);
				break;
			default:
				break;
			}
		}
	}
}