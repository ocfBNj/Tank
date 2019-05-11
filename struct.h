#ifndef _STRUCT_H_
#define _STRUCT_H_

#include <graphics.h>
#pragma comment(lib, "MSIMG32.LIB")

// 透明贴图函数
// 参数：
//		dstimg: 目标 IMAGE 对象指针。NULL 表示默认窗体
//		x, y:	目标贴图位置
//		srcimg: 源 IMAGE 对象指针。NULL 表示默认窗体
//		transparentcolor: 透明色。srcimg 的该颜色并不会复制到 dstimg 上，从而实现透明贴图
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor);

//窗口大小
#define WINDOW_WIDTH	768
#define WINDOW_HEIGHT	672

//中间黑色游戏区域
#define CENTER_WIDTH	624
#define CENTER_HEIGHT	624

//游戏区域相对左上角的坐标
#define CENTER_X		48
#define CENTER_Y		27

//箭头位置
#define ARROWS_X        210
#define ARROWS_Y        369
#define ARROWS_DIS      45

//方块大小
#define BLOCK_SIZE      24

//子弹大小
#define BULLET_SIZE     12

//方向
enum Dir {
	LEFT, UP, RIGHT, DOWN
};

#endif // !_STRUCT_H_