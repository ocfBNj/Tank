#include "Timer.h"


void Timer::start() {
	begin = std::chrono::steady_clock::now();
}

void Timer::stop() {
	end = std::chrono::steady_clock::now();
}

double Timer::times() {
	//将时间段转为毫秒
	std::chrono::duration<double, std::ratio<1, 1000>> times = end - begin;
	return times.count();
}
