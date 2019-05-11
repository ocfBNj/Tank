#include "SelectPanel.h"
#include "struct.h"
#include "GameControl.h"
#include "Timer.h"
#include <iostream>

int main(void) {
	srand((unsigned)time(NULL));
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);            //窗口大小
	BeginBatchDraw();                                  //开始批量绘图

	while (1) {
		SelectPanel s;                                     //选择面板
		s.select();
		GameControl gm;                                    //控制游戏
		gm.gameLoop();
	}

	EndBatchDraw();                                    //结束批量绘图
	closegraph();                                      //关闭窗口
	return 0;
}