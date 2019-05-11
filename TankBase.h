#ifndef _TANK_BASE_
#define _TANK_BASE_

#include "struct.h"

class TankBase {
public:
	TankBase(int _x, int _y, Dir d, int s, int b);
	virtual ~TankBase() = default;
	int getX() const;
	int getY() const;
	Dir getDir() const;
	void adjust();                    //碰撞后调整位置
	bool isMoving();                  //自动移动是否开启
	void died();                      //死亡后处理残留图片
	void disBlood();                  //掉一点血
	bool haveDied();                  //死亡
protected:
	int x, y;                         //坦克（左上角）坐标
	Dir dir;                          //方向
	bool flag_move;                   //自动移动标记
	int speed;                        //坦克速度
	int cur_blood;                    //当前血量
	int cur_shape;                    //当前造型
	int steep;                        //自动移动时移动了的步数

	void changeShape();               //切换造型
	void autoMove();                  //开启自动移动
	void stopMove();                  //停止自动移动
	void clearOld() const;            //清理旧图
};

#endif // !_TANK_BASE_