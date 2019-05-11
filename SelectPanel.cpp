#include "SelectPanel.h"

SelectPanel::SelectPanel() : arrows_pos(1), cur_shape(0) {
	//加载图片
	loadimage(&select_img, _T(".\\res\\image\\select_player.gif"));
	loadimage(&arrows_img[0], _T(".\\res\\image\\0Player\\m0-2-1.gif"));
	loadimage(&arrows_img[1], _T(".\\res\\image\\0Player\\m0-2-2.gif"));
}

void SelectPanel::runUp() {
	char c = 0;
	for (int y = WINDOW_HEIGHT; y > 0; y -= 4) {
		if (_kbhit()) //输入回车跳过动画
			if ((c = _getch()) == '\r') break;
		transparentimage(NULL, 0, y, &select_img, 0xffc4c4);
		FlushBatchDraw();
		Sleep(66);
	}
	transparentimage(NULL, 0, 0, &select_img, 0xffc4c4);
	FlushBatchDraw();
}

inline void SelectPanel::changeShape() {
	if (cur_shape == 0)
		cur_shape = 1;
	else
		cur_shape = 0;
}

inline void SelectPanel::showArrow() {
	transparentimage(NULL, ARROWS_X, ARROWS_Y + (arrows_pos - 1) * ARROWS_DIS, &arrows_img[cur_shape], 0xffc4c4);
	FlushBatchDraw();
	Sleep(10);
	changeShape();
}

int SelectPanel::moveArrows() {
	showArrow();
	char c = 0;
	if (_kbhit()) {
		c = _getch();
		if (c == 'w') {
			clearOld();
			if (arrows_pos > 1 && arrows_pos <= 3)
				--arrows_pos; //向上移动
			else
				arrows_pos = 3;
		} else if (c == 's') {
			clearOld();
			if (arrows_pos >= 1 && arrows_pos < 3)
				++arrows_pos; //向下移动
			else
				arrows_pos = 1;
		} else if (c == '\r') {
			return arrows_pos;
		}
	}
	return 0;
}

inline void SelectPanel::clearOld() {
	clearrectangle(ARROWS_X, ARROWS_Y + (arrows_pos - 1) * ARROWS_DIS,
		ARROWS_X + BLOCK_SIZE * 2, ARROWS_Y + (arrows_pos - 1) * ARROWS_DIS + BLOCK_SIZE * 2);
}

SelectResult SelectPanel::select() {
	SelectResult ret;
	runUp();//显示上升动画

	//移动箭头
	while (!(ret = (SelectResult)moveArrows()));

	return ret;
}