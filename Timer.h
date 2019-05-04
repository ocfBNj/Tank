#pragma once

#include <chrono>
class Timer {
public:
	Timer() = default;
	void start();
	void stop();
	double times();
private:
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
};

