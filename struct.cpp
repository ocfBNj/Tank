#include "struct.h"

void transparentimage(IMAGE *dstimg, int x, int y, IMAGE *srcimg, UINT transparentcolor) {
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();

	// 使用 Windows GDI 函数实现透明位图
	TransparentBlt(dstDC, x, y, w * 3, h * 3, srcDC, 0, 0, w, h, transparentcolor);
}

