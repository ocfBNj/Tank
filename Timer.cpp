#include "Timer.h"


Timer::Timer() : dif_time() {}

void Timer::setDifTime(double t) {
	dif_time = t;           //设置时间段
	start();                //开始计时
}

bool Timer::isTimeOut() {
	stop(); //获得结束时间以便计算时间差
	if (times() >= dif_time) {
		start(); //重新计时
		return true;
	}
	return false;
}

inline void Timer::start() {
	begin = std::chrono::steady_clock::now();
}

inline void Timer::stop() {
	end = std::chrono::steady_clock::now();
}

inline double Timer::times() {
	//将时间段转为毫秒
	std::chrono::duration<double, std::ratio<1, 1000>> times = end - begin;
	return times.count();
}
