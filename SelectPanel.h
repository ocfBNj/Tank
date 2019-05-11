#ifndef  _SELECT_PANEL_H_
#define _SELECT_PANEL_H_

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
	SelectResult select();

private:
	void runUp();                    //上升动画
	void changeShape();              //改变箭头造型
	void showArrow();                //显示箭头
	int moveArrows();                //移动箭头位置
	void clearOld();                 //清理残留贴图

	IMAGE select_img;                //选择界面图片
	IMAGE arrows_img[2];             //箭头图片
	int arrows_pos;                  //箭头位置
	int cur_shape;                   //箭头当前造型
};

#endif // ! _SELECT_PANEL_H_