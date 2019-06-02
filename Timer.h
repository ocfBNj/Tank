#pragma once

#include <chrono>
class Timer {
public:
	Timer();
	void setDifTime(double t);    
	bool isTimeOut();                                   //时间到
	
private:
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	double dif_time;                                    //记录时间间隔

	void start();                                       //开始计时
	void stop();                                        //获得结束时间
	double times();                                     //计算时间差
};

