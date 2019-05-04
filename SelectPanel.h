#pragma

#include "struct.h"
#include <graphics.h>
#include <conio.h>

//选择结果
enum SelectResult {
	OnePlayer = 1,
	TwoPlater,
	Custom
};

class SelectPanel {
public:
	SelectPanel();
	SelectResult select();           //外部接口

private:
	void runUp();                    //上升动画
	void changeShape();              //改变箭头造型
	void showArrow();                //显示箭头
	int moveArrows();                //移动箭头位置

	IMAGE select_img;                //选择界面图片
	IMAGE arrows_img[2];             //箭头图片
	int arrows_pos;                  //箭头位置
	int cur_shape;                   //箭头当前造型
};

inline
SelectPanel::SelectPanel() :
	arrows_pos(1), cur_shape(0)
{
	//加载图片
	loadimage(&select_img, _T(".\\res\\image\\select_player.gif"));
	loadimage(&arrows_img[0], _T(".\\res\\image\\0Player\\m0-2-1.gif"));
	loadimage(&arrows_img[1], _T(".\\res\\image\\0Player\\m0-2-2.gif"));
}

inline
void SelectPanel::runUp() {
	char c = 0;
	for (int y = WINDOW_HEIGHT; y > 0; y -= 4) {
		if (_kbhit())//输入回车跳过动画
			if ((c = _getch()) == '\r') {
				break;
			}
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

inline
void SelectPanel::showArrow() {
	transparentimage(NULL, ARROWS_X, ARROWS_Y + (arrows_pos - 1) * ARROWS_DIS, &arrows_img[cur_shape], 0xffc4c4);
	FlushBatchDraw();
	Sleep(10);
	changeShape();
}

inline
int SelectPanel::moveArrows() {
	showArrow();
	static char c = 0;
	if (_kbhit()) {
		c = _getch();
		switch (c) {
		case 'w':
			if (arrows_pos > 1 && arrows_pos <= 3) {
				//清除当前位置的箭头
				clearrectangle(ARROWS_X, ARROWS_Y + (arrows_pos - 1) * ARROWS_DIS,
					ARROWS_X + BLOCK_SIZE * 2, ARROWS_Y + (arrows_pos - 1) * ARROWS_DIS + BLOCK_SIZE * 2);
				--arrows_pos;//向上移动
			}
			break;
		case 's':
			if (arrows_pos >= 1 && arrows_pos < 3) {
				clearrectangle(ARROWS_X, ARROWS_Y + (arrows_pos - 1) * ARROWS_DIS,
					ARROWS_X + BLOCK_SIZE * 2, ARROWS_Y + (arrows_pos - 1) * ARROWS_DIS + BLOCK_SIZE * 2);
				++arrows_pos;//向下移动
			}
			break;
		case '\r':
			return arrows_pos;
		default:
			break;
		}
	}
	return 0;
}

inline
SelectResult SelectPanel::select() {
	SelectResult ret;
	runUp();//显示上升动画

	//移动箭头
	while (!(ret = (SelectResult)moveArrows()));

	return ret;
}